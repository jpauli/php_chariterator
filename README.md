New Iterator iterating characters in a PHP string.
Multibyte characters are not supported

```php
<?php

var_dump(iterator_to_array(new CharIterator('foobarbaz')));

/*
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
*/
```

Chunk size is supported :

```php
<?php

var_dump(iterator_to_array(new CharIterator('foobarbaz', 3)));

/*
array(3) {
  [0]=>
  string(3) "foo"
  [1]=>
  string(3) "bar"
  [2]=>
  string(3) "baz"
}
*/

```
