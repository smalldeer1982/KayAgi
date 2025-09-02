# 题目信息

# [CCC 2022 S2] Good Groups

## 题目背景

请注意：这道题是 [CCO 2022 J4  Good Groups](https://www.luogu.com.cn/problem/P8403) 的加强版。

管理备注：似乎没有加强。

## 题目描述

一个班级会被分成 $g$ 个组，每个组有三个人，这种分组方式可能会违反两种规定：

1. 一些学生必须在同一小组；
2. 一些学生必须不在同一小组。

现在校长找到了你，问学生违反了多少个规定。

## 说明/提示

### 样例 2 解释：

1. $\rm A$ 和 $\rm B$ 必须在同一组，这一点违反了。
2. $\rm G$ 和 $\rm L$ 必须在同一组，这一点违反了。
3. $\rm J$ 和 $\rm K$ 必须在同一组，这一点没有违反。
4. $\rm D$ 和 $\rm F$ 必须不在同一组，这一点违反了。
5. $\rm D$ 和 $\rm G$ 必须不在同一组，这一点没有被违反。

以上 $5$ 条共违反 $3$ 条，所以输出 $3$。

对于 $20\%$ 的数据：$1\le g\le 50$，$1\le x\le 50$，$y=0$。

对于另外 $35\%$ 的数据：$1\le g\le 50$，$1\le x\le 50$，$1\le y\le 50$。
 
对于 $100\%$ 的数据：$1\le g\le 10^5$，$1\le x\le 10^5$，$1\le y\le 10^5$。

## 样例 #1

### 输入

```
1
ELODIE CHI
0
2
DWAYNE BEN ANJALI
CHI FRANCOIS ELODIE```

### 输出

```
0```

## 样例 #2

### 输入

```
3
A B
G L
J K
2
D F
D G
4
A C G
B D F
E H I
J K L```

### 输出

```
3```

# AI分析结果

• 综合分析与结论：这几道题解均围绕如何处理学生分组违反规定数量的计算。主要思路是将学生名字（字符串）转化为便于处理的数字，再通过不同方式判断分组是否违反规定。其中，有使用并查集来记录分组关系，也有通过简单模拟直接判断。处理字符串到数字的映射是关键，不同方法在效率和实现复杂度上有差异。
- LYqwq（4星）
  - 关键亮点：采用并查集记录分组情况，利用BKDR hash进行字符串哈希，解决字符串转数字问题，优化代码效率。
  - 个人心得：尝试多种哈希方法会WA，最终发现BKDR hash可通过，且需合理设置哈希参数及数组范围减少冲突。
  - 核心代码：
```cpp
// 字符串哈希
int hs(string s){
    unsigned int res=0;
    for(int i=0; i<s.size(); i++)
        res=res*63+s[i]; // BKDR 哈希
    return res%(int)1e7;
    // res需要作为数组下标，为了防止哈希冲突，将数组开到了 1e7
}
// 并查集
template<class T=int>
class set{
    public:
        set(int n=1e5){f=new T[l=n+5]; clear();}
        ~set(){delete[] f;}
        T find(T x){return f[x]==x? x : f[x]=find(f[x]);}
        void merge(T x,T y){f[find(x)]=find(y);}
        void clear(){for(int i=0; i<l; i++) f[i]=i;}
    private:
        T *f;
        int l;
};
set<int> s(1e7); 
```
核心实现思想：`hs`函数通过BKDR hash算法将字符串转为数字，作为并查集的下标。并查集`set`实现了查找和合并功能，用于记录和判断学生分组关系。
- Ginger_he（4星）
  - 关键亮点：利用`unordered_map`将学生名字映射成编号，结合并查集处理分组关系，思路清晰，代码简洁。
  - 核心代码：
```cpp
void build(string s)
{
	if(!mp[s])
	{
		mp[s]=++cnt;
		p[cnt]=cnt;
		v.push_back(cnt);
	}
}
int find(int x)
{
	if(x==p[x])
		return x;
	return p[x]=find(p[x]); 
}
```
核心实现思想：`build`函数通过`unordered_map`给每个字符串名字分配唯一编号，并初始化并查集。`find`函数实现并查集查找功能，用于后续判断分组是否符合规定。
- yeshubo_qwq（3星）
  - 关键亮点：简单模拟思路，直接用`map`将名字映射为小组编号，通过对比编号判断规定是否违反，实现较为直观。
  - 核心代码：
```cpp
void solve(){
		cin>>t1;
		for (i=1;i<=t1;i++)
			cin>>n1[0][i]>>n1[1][i];
		cin>>t2;
		for (i=1;i<=t2;i++)
			cin>>n2[0][i]>>n2[1][i];
		cin>>t3;
		for (i=1;i<=t3;i++){
			cin>>a>>b>>c;
			g[a]=g[b]=g[c]=i;
		}
		int ans=0;
		for (i=1;i<=t1;i++)
			if (g[n1[0][i]]!=g[n1[1][i]])
				ans++;
		for (i=1;i<=t2;i++)
			if (g[n2[0][i]]==g[n2[1][i]])
				ans++;
		cout<<ans;
	}
```
核心实现思想：`solve`函数先读入规定和小组信息，用`map`给每个学生名字赋予所在小组编号，最后通过对比编号统计违反规定的数量。

最优关键思路或技巧：使用并查集结合字符串哈希（如BKDR hash）或`unordered_map`进行字符串到数字的映射，能高效处理分组关系判断。

可拓展之处：此类题目属于集合关系判断问题，类似算法套路可用于处理元素分组、连通性判断等问题。

推荐题目：
- P1551 [USACO10OCT]Lake Counting S
- P1197 [JSOI2008]星球大战
- P3367 【模板】并查集

摘录个人心得：LYqwq尝试多种哈希方法解决字符串转数字问题，经历多次WA后发现BKDR hash可通过，强调合理设置哈希参数及数组范围对减少冲突的重要性。 

---
处理用时：28.29秒