# CovertToSuperMemo
小工具，能够批量制作可以导入SuperMemo的Q&amp;A文档。现在可导入单词

# 原理

SuperMemo可以导入Q&A格式的文本文档。
Shanbay网有网络接口可以输入单词，查看单词的意思。

# 背单词步骤

1. 制作 word.txt 文件。一行一个单词。
2. 工具自动搜索每一个单词的意思
3. 将所有单词的意思组合，生成 wordSuperMemo.txt
4. 将 wordSuperMemo.txt 导入 SuperMemo
5. 利用SuperMemo背单词


# install
`gem install pg -v '0.21.0' --  --with-opt-dir='/usr/local/Cellar/libpq/12.4/'`