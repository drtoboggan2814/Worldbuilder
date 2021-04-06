#! /usr/bin/perl -w

use strict;

use Text::CSV_XS;
use Getopt::Std;
use Text::Wrap qw(wrap $columns);
$columns=72;

my %opt=(
  o => 'output.dot'
);

getopts('r:o:h',\%opt);

if (exists $opt{h}) {
  print STDERR <<EOF;
usage: $0 <options> <coordinate-file>
-r F : plot jump routes / Delaunay edges from file F
-o F : output dotfile to F
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

my $nodecount=0;
my %terminal;

open OUT,">$opt{o}";
print OUT <<EOF;
strict graph map {
  graph [overlap=false];
EOF
if (defined $opt{r}) {
  open DELAUNAY,"<$opt{r}";
  while (<DELAUNAY>) {
    chomp;
    my @s=split ' ',$_;
    my $orig=shift @s;
    $orig =~ s/\D//g;
    print OUT "  $orig -- { ".join(' ',@s)," };\n";
    if (scalar @s == 1) {
      $terminal{$orig}=1;
    }
  }
}

while (<>) {
  s/[\x00-\x1f]//g;
  $csv->parse($_);
  my @l=$csv->fields;
  my %data=map {$fields[$_] => $l[$_]} 0..$#fields;
  if ($data{name}) {
    print OUT "  $nodecount [label = \"$data{name}\"";
    if (exists $terminal{$nodecount}) {
      print OUT " fontcolor=red";
    }
    print OUT "];\n";
    $nodecount++;
  }
}

print OUT <<EOF;
}
EOF
