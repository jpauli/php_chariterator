--TEST--
Check for charit presence
--SKIPIF--
<?php if (!extension_loaded("charit")) print "skip"; ?>
--FILE--
<?php 
echo "charit extension is available";
?>
--EXPECT--
charit extension is available
