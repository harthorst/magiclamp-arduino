#/usr/bin/perl

my $max_leds = 261;
my $x = 0;
my $y = 0;

my $count_down = 15;
my $count_up = 14;

my $up = 0;

print "\n";
for (my $i=0; $i < $max_leds; $i++) {
  if ($i>0) {
    print ", ";
  }

  if ($y == ($count_down) * 2) {
    $up = 1;
    $x = $x + 1;
    $y = $y -3;
    print "\n";
  } elsif ($y == -1) {
    $up = 0;
    $x = $x + 1;
    $y = 0;
    print "\n";
  }

  printf "{%3s, %3s}", $x, $y;

  if ($up) {
    $y = $y - 2;
  } else {
    $y = $y + 2;
  }
}

print "\n\n";

for (my $i=0; $i < $max_leds; $i++) {
  if ($i % ($count_down + $count_up) == 0) {
    if ($i>0) {
      print ", ";
      print ($i-1);
    }
    print ", $i";
  }


}

print "\n\n";
for (my $i=0; $i < $max_leds; $i++) {
  if ($i % ($count_down + $count_up) - $count_down == 0) {
    if ($i>0) {
      print ", ";
      print ($i-1);
    }
    print ", $i";
  }
}
