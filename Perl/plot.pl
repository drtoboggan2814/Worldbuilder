#! /usr/bin/perl -w

use strict;

use Data::Dumper;

use Text::CSV_XS;
use Getopt::Std;
use GD;

my $qhull='qhull';

my %opt=(
  B => '000000',
  S => 'FFFFFF',
  V => 'EF0707',
  R => '074CED',
  s => 500,
  o => 'output.png',
  x => 'x',
  y => 'y'
);
getopts('s:v:p:r:o:x:y:A:P:V:R:S:B:h',\%opt);

if (exists $opt{h}) {
  print STDERR <<EOF;
usage: $0 <options> <coordinate-file>
-s N : output image will be N x N pixels
-v F : plot Voronoi vertices from file F
-p F : plot Voronoi polytopes from file F
-r F : plot jump routes / Delaunay edges from file F
-o F : write output image to file F (default $opt{o})
-x N : use axis "N" as the X axis
-y N : use axis "N" as the Y axis
-B N : set background to hex colour (default $opt{B})
-S N : set stars to hex colour (default $opt{S})
-V N : set Voronoi edges to hex colour (default $opt{V})
-R N : set jump routes to hex colour (default $opt{R})
-h   : this message
EOF
  exit 0;
}

# -z N : use axis "N" as the Z axis (and force 3-D plot)
# -A N : set alpha to N degrees (3d view only)
# -P N : set phi to N degrees (3d view only)

my $img=GD::Image->new($opt{s},$opt{s});

my %colour;
use Data::Dumper;
foreach my $i (qw(B S V R)) {
  my @c=($opt{$i} =~ /([\dA-F]{2})/g);
  splice @c,3;
  @c=map{hex($_)} @c;
  $colour{$i}=$img->colorAllocate(@c);
}

my $csv=Text::CSV_XS->new;

my @fields;
my @cfields;
my %cfmap;
my $dim=2;
my $plotdim=2;
if (exists $opt{z}) {
  $plotdim=3;
}
{
  my $l=<>;
  $csv->parse($l);
  @fields=$csv->fields;
  @cfields=grep /^.$/,@fields;
  if (scalar @cfields >= 2) {
    $dim=scalar @cfields;
  } else {
    die "Can't find enough single-letter field names in input file.\n";
  }
  %cfmap=map {$_ => $cfields[$_]} 0..$#cfields;
}
my @coords;
my @max;
my @min;
while (<>) {
  s/[\x00-\x1f]//g;
  $csv->parse($_);
  my @l=$csv->fields;
  my %data=map {$fields[$_] => $l[$_]} 0..$#fields;
  my @c=map {$data{$_}} @cfields;
  foreach my $n (0..$dim-1) {
    if (defined($max[$n])) {
      $max[$n]=&max($max[$n],$c[$n]);
    } else {
      $max[$n]=$c[$n];
    }
    if (defined($min[$n])) {
      $min[$n]=&min($min[$n],$c[$n]);
    } else {
      $min[$n]=$c[$n];
    }
  }
  push @coords,\@c;
}
my @plotfields=($opt{x},$opt{y});
if (exists $opt{z}) {
  push @plotfields,$opt{z};
}

my @scale=map {$opt{s}/($max[$_]-$min[$_])} 0..$dim-1;

if (defined $opt{v} && defined($opt{p})) {
  open VVERT,"<$opt{v}";
  my @ifields;
  my @vvert;
  my @vpoly;
  {
    my $l=<VVERT>;
    $csv->parse($l);
    @ifields=$csv->fields;
  }
  while (<VVERT>) {
    s/[\x00-\x1f]//g;
    $csv->parse($_);
    my @l=$csv->fields;
    my %data=map {$fields[$_] => $l[$_]} 0..$#fields;
    my @c=map {$data{$_}} @cfields;
    push @vvert,\@c;
  }
  close VVERT;
  open VPOLY,"<$opt{p}";
  while (<VPOLY>) {
    s/[\x00-\x1f]//g;
    push @vpoly,[split ' ',$_];
  }
  close VPOLY;
  foreach my $poly (@vpoly) {
    my @l=@{$poly};
    push @l,$l[0];
    foreach my $n (0..$#l-1) {
      if ($l[$n]>0 && $l[$n+1]>0) {
        $img->line(&coords($vvert[$l[$n]]),&coords($vvert[$l[$n+1]]),$colour{V});
      }
    }
  }
}

if (defined $opt{r}) {
  open DELAUNAY,"<$opt{r}";
  while (<DELAUNAY>) {
    chomp;
    my @s=split ' ',$_;
    my $orig=shift @s;
    $orig =~ s/\D//g;
    foreach my $dest (@s) {
      if ($dest>$orig) {
        $img->line(&coords($coords[$orig]),&coords($coords[$dest]),$colour{R});
      }
    }
  }
}

foreach my $s (@coords) {
  $img->filledRectangle(&coords($s,[-1,-1]),&coords($s,[1,1]),$colour{S});
}

if (defined $opt{o}) {
  open OUT,">$opt{o}";
  binmode OUT;
  print OUT $img->png;
  close OUT;
}

sub coords {
  my ($coords,$delta)=@_;
  my @c=@{$coords};
  if (scalar @c > $plotdim) {
    my %t=map {$cfields[$_] => $c[$_]} 0..$#cfields;
    @c=map {$t{$_}} @plotfields;
  }
  if ($plotdim==2) {
    @c=map {($c[$_]-$min[$_])*$scale[$_]} 0..$plotdim-1;
    $c[1]=$opt{s}-1-$c[1];
  } elsif ($plotdim==3) { # write this
  }
  if (defined $delta) {
    @c=map {$c[$_]+$delta->[$_]} 0..1;
  }
  return @c;
}

sub max {
  my @t=@_;
  my $a=$t[0];
  foreach my $b (@t[1..$#t]) {
    if ($b>$a) {
      $a=$b;
    }
  }
  return $a;
}

sub min {
  my @t=@_;
  my $a=$t[0];
  foreach my $b (@t[1..$#t]) {
    if ($b<$a) {
      $a=$b;
    }
  }
  return $a;
}

sub sqdist {
  my ($a,$b)=@_;
  my $d=0;
  foreach my $n (0..$#{$a}) {
    $d+=($a->[$n]-$b->[$n])**2;
  }
  return $d;
}
