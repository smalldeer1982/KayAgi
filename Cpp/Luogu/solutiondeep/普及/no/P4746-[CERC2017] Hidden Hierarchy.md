# 题目信息

# [CERC2017] Hidden Hierarchy

## 题目描述

假设你正在开发一个简单的以输入文字为基础的文件夹浏览器。你的工作之一就是要构建一个导航目录来显示这些文件夹的上下关系。通常而言，这些文件夹很可能是互相嵌套的——比如，某个文件夹下还有一个文件夹，当然也可能会包含某些文件。因此，这些文件夹会形成一种树状结构。在这个目录中，最顶端的那个文件夹称之为根目录。如果文件夹d中直接含有文件夹e，那么我们称之为文件夹d是文件夹e的父文件夹，而文件夹e是文件夹d的子文件夹。每个文件都有一个用字节数来表示的大小。一个文件夹的大小是被直接或不直接包含于其中的所有文件的大小之和。

所有的文件和文件夹（除根目录外）都有一个名字——一个只由小写字符和点（“."）组成并且只由小写字母开头的字符串。包含于同一个父目录下的文件或文件夹的名字必定各不相同。而且，路径与文件是一一对应的。生成路径的规则如下：

- 根目录路径是“/”
- 文件夹d的路径是从根目录开始，沿着文件夹的父子关系，顺次往下，在每个文件夹名字前添加一个“/”，相互连接，并在路径的最末尾添加一个“/”。
- 文件f的路径是由它的父文件夹的路径加上文件名得到的。

通过打印根目录，我们能够显示文件夹的上下父子关系。打印文件夹d时，我们输出一个“md pd sd”形式的字符串。其中，pd是文件夹d的路径，sd是文件夹d的大小，md是文件夹d的扩展标记。如果文件夹d包含其他文件夹，我们可以选择是否展开它。如果我们要展开文件夹d，我们就要以字典序打印它里面包含的所有文件和文件夹。如果我们不打开文件夹d，那么我们就可以忽略其中的内容。

如果d是一个空文件夹（即没有包含任何文件或文件夹），那么md就仅仅是一个空字符。当我们要展开这个文件夹的时候，md是一个“-”，而如果我们不展开这个文件夹的是md是一个“+”。

现在，输入一列文件和一个限制性整数t。请你打印（按照前述展开打印方法）所有的大小不小于t的文件夹。并且，打印的文件夹总数一定是最小的。保证不存在空文件夹即整个文件夹上下关系都可从输入的文件路径中推断得出。注意，大小不小于t的文件夹必须要被打印，但不一定要展开。根目录不论多大都要被打印。

## 样例 #1

### 输入

```
9
/sys/kernel/notes 100
/cerc/problems/a/testdata/in 1000000
/cerc/problems/a/testdata/out 8
/cerc/problems/a/luka.cc 500
/cerc/problems/a/zuza.cc 5000
/cerc/problems/b/testdata/in 15
/cerc/problems/b/testdata/out 4
/cerc/problems/b/kale.cc 100
/cerc/documents/rules.pdf 4000
10000```

### 输出

```
- / 1009727
- /cerc/ 1009627
/cerc/documents/ 4000
- /cerc/problems/ 1005627
- /cerc/problems/a/ 1005508
/cerc/problems/a/testdata/ 1000008
+ /cerc/problems/b/ 119
+ /sys/ 100
```

## 样例 #2

### 输入

```
8
/b/test/in.a 100
/b/test/in.b 1
/c/test/in.a 100
/c/test/in.b 1
/c/test/pic/in.a.svg 10
/c/test/pic/in.b.svg 10
/a/test/in.a 99
/a/test/in.b 1
101
```

### 输出

```
- / 322
+ /a/ 100
- /b/ 101
/b/test/ 101
- /c/ 121
+ /c/test/ 121```

## 样例 #3

### 输入

```
2
/a/a/a 100
/b.txt 99
200
```

### 输出

```
+ / 199
```

# AI分析结果



**算法分类**  
模拟、深度优先搜索 (DFS)

**综合分析与结论**  
本题需构建文件夹的树状结构，计算各节点大小后按规则展开输出。题解普遍采用双 `map` 存储子节点和大小，两次 DFS 分别计算大小和输出。但部分代码存在路径处理错误或展开逻辑漏洞，未能完全满足题目“仅打印大小不小于 `t` 的目录且总数最小”的条件。正确思路应结合后序遍历标记必须打印的目录（包括父目录需展开的情况），并确保根目录强制打印。

**推荐题目**  
1. P1038 [NOIP2003 提高组] 神经网络（树状结构处理）  
2. P1271 取石子游戏（树形条件展开）  
3. P2014 [CTSC1997] 选课（树形依赖与动态规划）  

---

**关键思路与优化**  
1. **树构建**：通过分割路径建立父子关系，使用 `map<string, set<string>>` 存储子节点，`map<string, ll>` 存储大小。
2. **后序遍历标记**：递归计算目录大小时，标记需打印的目录（自身大小≥`t` 或包含需打印的子目录）。
3. **输出逻辑**：根目录强制输出，其余按需展开（存在需打印的子目录则展开标记为 `-`，否则折叠为 `+`）。

**核心代码片段（示例）**  
```cpp
// 构建树与计算大小
void buildTree() {
    for (auto& [path, size] : files) {
        string parent = "/";
        for (每个目录层级 dir) {
            parent += dir + "/";
            son[parent].insert(dir);
            folderSize[parent] += size;
        }
    }
}

// 标记需打印的目录（伪代码）
bool markPrint(Node* node) {
    bool need = node->size >= t;
    for (auto child : node->children) {
        if (markPrint(child)) need = true;
    }
    if (node->isRoot) need = true;
    node->needPrint = need;
    return need;
}

// 按需输出
void printTree(Node* node) {
    if (!node->needPrint) return;
    cout << (展开条件 ? "-" : "+") << " " << node->path << " " << node->size << endl;
    if (需展开) for (auto child : sorted_children) printTree(child);
}
```

---
处理用时：344.64秒