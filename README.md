# minishell_42

A propos de readline:

```
brew install readline
```

make && valgrind --suppressions=./minimal.supp --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all ./minishell