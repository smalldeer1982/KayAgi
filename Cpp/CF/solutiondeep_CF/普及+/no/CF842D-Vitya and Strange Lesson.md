# 题目信息

# Vitya and Strange Lesson

## 题目描述

## 问题描述
mex 是一个序列中没有出现过的最小非负整数。

给出你一个长度为 $n$  的非负整数序列以及 $m$  个询问，每次询问先给你一个整数 $x$ ，然后：

- 把序列中所有数异或上 $x$ 
- 输出序列的 mex

注意，在每个询问过后序列是发生变化的。

## 样例 #1

### 输入

```
2 2
1 3
1
3
```

### 输出

```
1
0
```

## 样例 #2

### 输入

```
4 3
0 1 5 6
1
2
4
```

### 输出

```
2
0
0
```

## 样例 #3

### 输入

```
5 4
0 1 5 6 7
1
1
4
5
```

### 输出

```
2
2
0
2
```

# AI分析结果

### 题目内容
# Vitya和奇怪的课程

## 题目描述
mex是一个序列中没有出现过的最小非负整数。
给出你一个长度为 $n$ 的非负整数序列以及 $m$ 个询问，每次询问先给你一个整数 $x$ ，然后：
- 把序列中所有数异或上 $x$ 
- 输出序列的mex
注意，在每个询问过后序列是发生变化的。

## 样例 #1
### 输入
```
2 2
1 3
1
3
```
### 输出
```
1
0
```

## 样例 #2
### 输入
```
4 3
0 1 5 6
1
2
4
```
### 输出
```
2
0
0
```

## 样例 #3
### 输入
```
5 4
0 1 5 6 7
1
1
4
5
```
### 输出
```
2
2
0
2
```
### 算法分类
位运算

### 综合分析与结论
这些题解都围绕如何利用数据结构高效解决序列异或后求mex的问题。各题解思路相近，均考虑到异或操作和mex计算的特点，最终选用01trie数据结构。难点在于如何结合01trie实现异或操作与mex的高效查询。多数题解利用01trie按位存储数字的特性，通过记录节点子树大小判断子树是否满，在查询mex时，根据异或值决定遍历方向。同时，插入数字时需去重避免影响子树大小统计。

### 所选的题解
- **作者：试试事实上吗 (5星)**
    - **关键亮点**：思路清晰，详细阐述从考虑线性基、值域线段树到确定01trie的过程，对01trie上二分查mex及异或操作的实现讲解透彻。
    - **个人心得**：感慨该问题经典却不知，从思考常用操作异或集合手段入手逐步找到解法。
    - **重点代码**：
```cpp
void insert(int x,int u=1,int now=Lim)
{
    if(now==-1) return siz[u]=1,void();
    int s=x>>now&1;
    if(!tr[u][s]) tr[u][s]=++cnt;
    insert(x,tr[u][s],now-1);
    siz[u]=siz[tr[u][0]]+siz[tr[u][1]];
}

inline int query(int x=nowxor)
{
    int u=1,res=0;
    for(int i=Lim;i>=0;--i)
    {
        int s=x>>i&1;
        if(siz[tr[u][s]]==((1<<i))) u=tr[u][s^1],res|=(1<<i);
        else u=tr[u][s];
        if(!u) return res;
    }
    return res;
}
```
核心实现思想：`insert`函数向01trie插入数字，`query`函数在01trie上根据异或值查询mex。
- **作者：Taduro (4星)**
    - **关键亮点**：对01trie概念解释清晰，指出其与普通trie树区别，代码有小优化。
    - **重点代码**：
```cpp
inline void insert(int x){
	int u=1;
	for (int i=maxn; i>=0; i--){
		int a=((x&(1<<i))!=0);
		if (!t[u][a]) t[u][a]=++num;
		sum[u][a]++;u=t[u][a];
	}
}
inline int query(){
	int u=1,ans=0;
	for (int i=maxn; i>=0; i--){
		int a=((k&(1<<i))!=0);
		if (sum[u][a]<(1<<i)){
			u=t[u][a]; if (!u) return ans;
		}
		else{
			u=t[u][a^1];
			ans|=(1<<i); if (!u) return ans;
		}
	}
	return ans;
}
```
核心实现思想：`insert`函数插入数字到01trie，`query`函数依据异或值在01trie查询mex。
- **作者：Gloaming (4星)**
    - **关键亮点**：先分析常规求mex方法及不足，引出01trie解法，结合图形观察得出01trie上子树与连续数字关系，思路连贯。
    - **重点代码**：
```cpp
inline void Ins(int cur,int weis,int x){
	if(weis<0) {sz[cur]=1;return;}
	int ch=x>>weis&1;
	if(tr[cur][ch]==0) tr[cur][ch]=++tot;
	Ins(tr[cur][ch],weis-1,x);
	sz[cur]=sz[tr[cur][0]]+sz[tr[cur][1]];
}
inline int Qry(int cur,int axor){
	int res=0;
	for(int weis=25;weis>=0;weis--){
		int ch=axor>>weis&1;
		if(sz[tr[cur][ch]]==(1<<(weis))) {
			res|=(1<<(weis));
			cur=tr[cur][ch^1];
		} else {
			cur=tr[cur][ch];
		}
		if(cur==0) return res;
	}
	return res;
}
```
核心实现思想：`Ins`函数用于在01trie插入数字，`Qry`函数根据异或值在01trie上查询mex。

### 最优关键思路或技巧
利用01trie按位存储数字的特性，通过记录节点子树大小判断子树是否满，在查询mex时根据异或值决定遍历方向，避免每次询问对序列所有数字进行异或操作，从而降低时间复杂度。同时，插入数字去重保证子树大小统计准确。

### 可拓展之处
同类型题常涉及对序列进行特定位运算操作后查询某种极值或统计量。类似算法套路是利用数据结构（如01trie）处理位运算，结合统计信息（如子树大小）实现高效查询。

### 洛谷相似题目
- [P3834 【模板】可持久化线段树 2（主席树）](https://www.luogu.com.cn/problem/P3834)
- [P4556 [Vani有约会]雨天的尾巴 /【模板】线段树合并](https://www.luogu.com.cn/problem/P4556)
- [P2042 维护数列](https://www.luogu.com.cn/problem/P2042) 

---
处理用时：65.41秒