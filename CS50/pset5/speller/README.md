# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

A word, a .txt file at keys/, a lung disease caused by inhaling ash, and the example of maximum length for a word.

## According to its man page, what does `getrusage` do?

Returns the resource usage measures for self, children or thread.

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

The getrusage function's input must be a pointer.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

Main begins reading from the file with a for-loop that iterates over each character using fgetc and checking for the EOF.
Main reads the file using a for-loop that receives as input a character given by fgetc and checks for EOF.
Then, it checks if the character is either a letter or an apostraphe. If so, it builds a string called word.
Then, it checks to see if the length of word is greater than the maximum word length. If it is, it consumes the remainder of the alphabetical string
and resets the index to 0. If the character isn't a letter or an apostraphe, it checks if the character is a number. If so, it consumes the remainder of alphanumeric string, resets the index to 0 and continues.
By now, if the index is not 0, it must be a word, so it appends \0 to mark end of a string and
adds one to the the word count. Then it uses check to make sure the word is in the given dictionary. If not, it adds one to misspellings. Then it resets the index to zero and loops until EOF.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

fgetc has the advantage of a more local approach, thus we can use white space to denote end of word, making it a better tool for the job.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

Since you're only reading the elements, there is no need for dynamism, so constants would be safer (if you accidentaly tried to change them).



