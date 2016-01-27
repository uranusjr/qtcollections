# QtCollections

More container classes for Qt, inspired by Python's [collections] module. Currently only `OrderedDict` is implemented (`qtcollections::OrderedHash`).


## License

QtColelctions is released under the terms of MIT License. You may find the content of the license [here](http://opensource.org/licenses/MIT), or in the `LICENSE` file.


## Implementation Details

### `OrderedHash`

The ordered hash is implemented with a `QHash` for its underlying storage, and a `QLinkedList` to keep track of key ordering. An extra `QHash` is used for reverse lookup, so that removal of any item can be guarenteed `O(1)`.

Compared with [qt-ordered-map], a project providing the same container, this implementation is more memory-heavy, but should be better in performance, especially for const operations. The API is also more in-line with standard Qt containers, especially in Qt 5.

[collections]: https://docs.python.org/3/library/collections.html
[qt-ordered-map]: https://github.com/mandeepsandhu/qt-ordered-map
