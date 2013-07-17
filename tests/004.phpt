--TEST--
Check for constructor exception with $chunk parameter too big
--SKIPIF--
<?php if (!extension_loaded("charit")) print "skip"; ?>
--FILE--
<?php 
try {
    new CharIterator('foo', 400);
    echo "failed";
} catch (OutOfRangeException $e) {
    echo "passed";
}
?>
--EXPECT--
passed
