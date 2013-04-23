--TEST--
Check for charit presence
--SKIPIF--
<?php if (!extension_loaded("charit")) print "skip"; ?>
--FILE--
<?php 
var_dump(iterator_to_array(new CharIterator('foobarbaz')));
?>
--EXPECT--
array(9) {
  [0]=>
  string(1) "f"
  [1]=>
  string(1) "o"
  [2]=>
  string(1) "o"
  [3]=>
  string(1) "b"
  [4]=>
  string(1) "a"
  [5]=>
  string(1) "r"
  [6]=>
  string(1) "b"
  [7]=>
  string(1) "a"
  [8]=>
  string(1) "z"
}
