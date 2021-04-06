#! /usr/bin/perl -w

use strict;

use Text::CSV_XS;
use Getopt::Std;
use File::Temp qw(tempfile);

#	Store qhull
my $qhull='qhull';

#	Program options
my %opt;
getopts('d:v:p:r:m:l:nsh',\%opt);

#	Print options
if (exists $opt{h}) {
  print STDERR <<EOF;
usage: $0 <options> <coordinate-file>
-d F : output Delaunay triangles to file F
-v F : output Voronoi vertices to file F
-p F : output Voronoi polytopes to file F
-m N : length culling: mark longest N edges per polytope (see documentation)
-l N : length culling: remove edges marked at least N times
-n   : Voronoi region culling (see documentation)
-s   : scale axes for equal weight
-r F : output jump routes to file F
-h   : this message
EOF
  exit 0;
}

#	Create a new csv variable
my $csv=Text::CSV_XS->new;

#	Row fields array
my @fields;
#	Column fields array
my @cfields;
#	Set the dimensions to be 1x2
my $dim=2;
{
#	Readline
  my $l=<>;
#	For the line $l, replace the regex pattern [\x00-\x1f] with blank
  $l =~ s/[\x00-\x1f]//g;
#	Parse the csv to find $l
  $csv->parse($l);
#	Set the array fields to the fields in $csv
  @fields=$csv->fields;
#	For each item in @fields, if there is any text, assign to @cfields
  @cfields=grep /^.$/,@fields;
#	The program needs at least two columns
  if (scalar @cfields >= 2) {
    $dim=scalar @cfields;
#	If there are not enough columns, kill the program and display an error message
  } else {
    die "Can't find enough single-letter field names in input file.\n";
  }
}
#	Declare an array for coordinates
my @coords;
#	Declare an array of max values
my @max;
#	Declare an array of min values
my @min;
#	While there is another line to grab
while (<>) {
#	Replace the regex pattern [\x00-\x1f] with blank
  s/[\x00-\x1f]//g;
#	Parse the default variable in $csv
  $csv->parse($_);
#	Assign fields in $csv to the array @l
  my @l=$csv->fields;
#	Map the contents in @fields to the hash %data from 0 to the number of items in @fields
  my %data=map {$fields[$_] => $l[$_]} 0..$#fields;
#	Map the contents in %data to @c in @cfields
  my @c=map {$data{$_}} @cfields;
#	For each $n in the range 0 to $dim - 1
  foreach my $n (0..$dim-1) {
#	If the value of @max at $n is defined
    if (defined($max[$n])) {
#		Between $max[$n] and $c[$n], assign the max value to $max[$n]
      $max[$n]=&max($max[$n],$c[$n]);
#	Else, the current value of @max is undefined
    } else {
#		Assign $c[$n] to $max[$n]
      $max[$n]=$c[$n];
    }
#	The same as above, but min
    if (defined($min[$n])) {
      $min[$n]=&min($min[$n],$c[$n]);
    } else {
      $min[$n]=$c[$n];
    }
  }
#	Append the values in @c to @coords
  push @coords,\@c;
}


# scale axes
#	If the option to scale the axes to equal height is set
if (exists $opt{s}) {
#	For each value from 0 to the number of items in @min
  foreach my $a (0..$#min) {
#		Assign the difference between the max and min to $m
    my $m=$max[$a]-$min[$a];
#		For each value $i from 0 to the number of items in @coords
    foreach my $i (0..$#coords) {
#			Assign the difference between the current coord and min divided by $m to the current coord
      $coords[$i][$a]=($coords[$i][$a]-$min[$a])/$m;
    }
#	Set the min and max values to 0 and 1, respectively
    $max[$a]=1;
    $min[$a]=0;
  }
}

# generate Voronoi partitioning
#	Create arrays for the vertices and polygons
my @vvertex;
my @vpoly;
#	If the vertices, polygons, or culling is being outputted
if (exists $opt{v} || exists $opt{p} || exists $opt{n}) {
#	Assign @coords to @cc
  my @cc=@coords;
#	Map to @centre half the sum of max and min at all values from 0 to $dim - 1
  my @centre=map {($max[$_]+$min[$_])/2} (0..$dim-1);
#	Map to @edge the difference between max and centre times three _ center for all values from 0 to $dim - 1
  my @edge=[map {($max[$_]-$centre[$_])*3+$centre[$_]} (0..$dim-1)];
#	Append the above to @edge
  push @edge,[map {($min[$_]-$centre[$_])*3+$centre[$_]} (0..$dim-1)];
#	For each value from 0 to (2^$dim) - 1
  foreach my $n (0..(2**$dim)-1) {
    my @c;
#	For each value $m from 0 to $dim - 1
    foreach my $m (0..$dim-1) {
      my $l=0;
#		If $n binary and 1 shifted left $m bits == 1
      if ($n & 1<<$m) {
#		  Set #l to 1
        $l=1;
      }
#	  Append the current edge value to @c
      push @c,$edge[$l][$m];
    }
#	Appendd @c to @cc
    push @cc,\@c;
  }
#	Create a tempfile
  my ($fh,$file)=tempfile;
#	External command with file handle "QHULL" to call qhull with options selected at runtime by the user
  open QHULL,"| $qhull v o TO $file";
#	Display $dim
  print QHULL "$dim\n";
#	Display @cc
  print QHULL scalar(@cc),"\n";
#	For each value $c in @cc, print $c
  foreach my $c (@cc) {
    print QHULL join(' ',@{$c}),"\n";
  }
  close QHULL;
#	Read each line in $fh
  <$fh>;
#	Remove \n from <$fh> and assign it to index
  chomp (my $index=<$fh>);
#	Assign the left and right to $vertices and $polytopes, respectively
  my ($vertices,$polytopes)=split ' ',$index;
#	While still reading <$fh>
  while (<$fh>) {
#	Replace the given pattern with blank
    s/[\x00-\x1f]//g;
#	For each value of <$fh>, split and assign it to @c
    my @c=split ' ',$_;
#	If there are vertices
    if ($vertices>0) {
#		Append @c to @vvertex
      push @vvertex,\@c;
#		Decrement vertices
      $vertices--;
    } elsif ($polytopes>0) {
      shift @c;
      push @vpoly,\@c;
      $polytopes--;
    }
  }
  unlink $file;
  if (exists $opt{v}) {
    open OUT,">$opt{v}";
    print OUT join(',',@cfields),"\n";
    foreach my $c (@vvertex) {
      print OUT join(',',@{$c}),"\n";
    }
    close OUT;
  }
  if (exists $opt{p}) {
    open OUT,">$opt{p}";
    foreach my $c (@vpoly) {
      print OUT join(' ',@{$c}),"\n";
    }
    close OUT;
  }
}

# generate Delaunay triangles
my @delaunay;
{
  my ($fh,$file)=tempfile;
  open QHULL,"| $qhull d i TO $file";
  print QHULL "$dim\n";
  print QHULL scalar(@coords),"\n";
#	Add points incrementally
  foreach my $c (@coords) {
    print QHULL join(' ',@{$c}),"\n";
  }
  close QHULL;
  if (exists $opt{d}) {
    open OUT,">$opt{d}";
  }
  <$fh>;
  while (<$fh>) {
    if (exists $opt{d}) {
      print OUT $_;
    }
    s/[\x00-\x1f]//g;
    my @c=split ' ',$_;
    push @delaunay,\@c;
  }
  unlink $file;
  if (exists $opt{d}) {
    close OUT;
  }
}

# do length culling
my %mark;
#	If options l and m are selected
if (exists $opt{l} && exists $opt{m}) {
#	For each 
  foreach my $d (@delaunay) {
    my %len;
    my @l=@{$d};
    push @l,$l[0];
    foreach my $n (0..$#l-1) {
      my $dist=&sqdist($coords[$l[$n]],$coords[$l[$n+1]]);
      my ($p1,$p2)=sort {$a <=> $b} ($l[$n],$l[$n+1]);
      $len{"$p1,$p2"}=$dist;
    }
    my @longest=sort {$len{$b} <=> $len{$a}} keys %len;
    splice @longest,$opt{m};
    foreach my $vp (@longest) {
      my ($p1,$p2)=split ',',$vp;
      unless (exists $mark{$p1}{$p2}) {
        $mark{$p1}{$p2}=0;
      }
      $mark{$p1}{$p2}++;
    }
  }
}

# generate routes
my %route;
{
  foreach my $d (@delaunay) {
    my @l=@{$d};
    push @l,$l[0];
    foreach my $n (0..$#l-1) {
      my $ok=1;
      if (exists $opt{l}) { # length culling
        my ($p1,$p2)=sort {$a <=> $b} ($l[$n],$l[$n+1]);
        if (exists $mark{$p1}{$p2} && $mark{$p1}{$p2}>=$opt{l}) {
          $ok=0;
        }
      }
      if (exists $opt{n}) { # Voronoi region culling
        my @midpoint=map {($coords[$l[$n]]->[$_] + $coords[$l[$n+1]]->[$_])/2} (0..$dim-1);
        my $mindist;
        my $st;
        foreach my $star (0..$#coords) {
          my $dist=&sqdist($coords[$star],\@midpoint);
          if (!defined($mindist) || $dist<$mindist) {
            $mindist=$dist;
            $st=$star;
          }
        }
        if ($st != $l[$n] && $st != $l[$n+1]) {
          $ok=0;
        }
      }
      if ($ok) {
        $route{$l[$n]}{$l[$n+1]}=1;
        $route{$l[$n+1]}{$l[$n]}=1;
      }
    }
  }
}

# dump route file
if (exists $opt{r}) {
  open OUT,">$opt{r}";
  foreach my $p1 (sort {$a <=> $b} keys %route) {
    print OUT "$p1:";
    foreach my $p2 (sort {$a <=> $b} keys %{$route{$p1}}) {
      print OUT " $p2";
    }
    print OUT "\n";
  }
  close OUT;
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
