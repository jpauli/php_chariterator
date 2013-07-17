--TEST--
Test for chunk size
--SKIPIF--
<?php if (!extension_loaded("charit")) print "skip"; ?>
--FILE--
<?php 
var_dump(iterator_to_array(new CharIterator('foobarbaz', 3)));
var_dump(iterator_to_array(new CharIterator('foobarbaz', 4)));
?>
--EXPECT--
array(3) {
  [0]=>
  string(3) "foo"
  [1]=>
  string(3) "bar"
  [2]=>
  string(3) "baz"
}
array(3) {
  [0]=>
  string(4) "foob"
  [1]=>
  string(4) "arba"
  [2]=>
  string(1) "z"
}
