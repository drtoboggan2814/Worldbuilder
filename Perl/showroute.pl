#! /usr/bin/perl -w

use strict;

use Text::CSV_XS;
use Getopt::Std;
use Text::Wrap qw(wrap $columns);
$columns=72;

my $qhull='qhull';

my %opt;

getopts('r:h',\%opt);

if (exists $opt{h}) {
  print STDERR <<EOF;
usage: $0 <options> <coordinate-file>
-r F : plot jump routes / Delaunay edges from file F
-h   : this message
EOF
  exit 0;
}

my $csv=Text::CSV_XS->new;

my @fields;
{
  my $l=<>;
  $csv->parse($l);
  @fields=$csv->fields;
}

my @names;

while (<>) {
  s/[\x00-\x1f]//g;
  $csv->parse($_);
  my @l=$csv->fields;
  my %data=map {$fields[$_] => $l[$_]} 0..$#fields;
  if ($data{name}) {
    push @names,$data{name};
  }
}

if (defined $opt{r}) {
  open DELAUNAY,"<$opt{r}";
  while (<DELAUNAY>) {
    chomp;
    my @s=split ' ',$_;
    my $orig=shift @s;
    $orig =~ s/\D//g;
    my @out;
    foreach my $dest (@s) {
      push @out,$names[$dest];
    }
    print wrap('',' ',"$names[$orig]: ".join(', ',@out)),"\n";
  }
}
