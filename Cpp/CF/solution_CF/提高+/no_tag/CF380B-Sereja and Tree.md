# Sereja and Tree

## 题目描述

Sereja adores trees. Today he came up with a revolutionary new type of binary root trees.

His new tree consists of $ n $ levels, each vertex is indexed by two integers: the number of the level and the number of the vertex on the current level. The tree root is at level $ 1 $ , its index is $ (1,1) $ . Here is a pseudo code of tree construction.

`<br></br>//the global data are integer arrays cnt[], left[][], right[][]<br></br><br></br>cnt[1] = 1;<br></br>fill arrays left[][], right[][] with values -1;<br></br>for(level = 1; level < n; level = level + 1){<br></br>    cnt[level + 1] = 0;<br></br>    for(position = 1; position <= cnt[level]; position = position + 1){<br></br>        if(the value of position is a power of two){ // that is, 1, 2, 4, 8...<br></br>            left[level][position] = cnt[level + 1] + 1;<br></br>            right[level][position] = cnt[level + 1] + 2;<br></br>            cnt[level + 1] = cnt[level + 1] + 2;            <br></br>        }else{<br></br>            right[level][position] = cnt[level + 1] + 1;<br></br>            cnt[level + 1] = cnt[level + 1] + 1;<br></br>        }<br></br>    }<br></br>}<br></br>`After the pseudo code is run, cell cnt\[level\] contains the number of vertices on level $ level $ . Cell left\[level\]\[position\] contains the number of the vertex on the level $ level+1 $ , which is the left child of the vertex with index $ (level,position) $ , or it contains -1, if the vertex doesn't have a left child. Similarly, cell right\[level\]\[position\] is responsible for the right child. You can see how the tree with $ n=4 $ looks like in the notes.

Serja loves to make things complicated, so he first made a tree and then added an empty set $ A(level,position) $ for each vertex. Then Sereja executes $ m $ operations. Each operation is of one of the two following types:

- The format of the operation is " $ 1 $ $ t $ $ l $ $ r $ $ x $ ". For all vertices $ level,position $ $ (level=t; l<=position<=r) $ add value $ x $ to set $ A(level,position) $ .
- The format of the operation is " $ 2 $ $ t $ $ v $ ". For vertex $ level,position $ $ (level=t,position=v) $ , find the union of all sets of vertices that are in the subtree of vertex $ (level,position) $ . Print the size of the union of these sets.

Help Sereja execute the operations. In this problem a set contains only distinct values like std::set in C++.

## 说明/提示

You can find the definitions that are used while working with root trees by this link: http://en.wikipedia.org/wiki/Tree\_(graph\_theory)

You can see an example of a constructed tree at $ n=4 $ below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF380B/cfdce7b6042e4b80c52bc12a850b34cb0c34fae6.png)

## 样例 #1

### 输入

```
4 5
1 4 4 7 1
1 3 1 2 2
2 1 1
2 4 1
2 3 3
```

### 输出

```
2
0
1
```

# 题解

## 作者：qjxqjx (赞：0)

## 题目思路：
由于题意有人解释了，所以我直接讲思路。

思路：$\boxed{\color{red}\textbf{暴力}}$

对于添加操作，可以在每一层用一个动态数组记录下所有的添加操作，只需记录 l，r 和 x。每当出现需要查询时，只需由根节点向下，遍历每层的 1 操作，判断是否对其造成影响。 然后比如在 i 层的区间是 $[x,y]$ ，到 $i+1$ 层时可以计算的出 $[xx,yy]$ ，没有必要一个一个去判断，那样必超时。

$xx=x+\log_2(x)$，$yy=y+\log_2(y)$ +(是否为 $2^k$ ? 1 : 0)。

但是如果一次一次去计算的话时间开销很大，会超时，必须在提前记录下所有下标的关系。

那么这题就迎刃而解了。

## 代码：
```c
#include <bits/stdc++.h>
//#include<set>
//#include<vector>
using namespace std;
const int N = 7005;
const int M = 200000;
struct state{
	int l, r, val;
	state(){}
	state(int l, int r, int val) {
		this->l = l; this->r = r; this->val = val;
	}
};
int n, m, dl[M], dr[M];
vector<state> v[N];//动态数组
int solve (int d, int x, int y) {
	set<int> ans;
	for (int i = d; i <= n; i++){
		for (int j=0;j<v[i].size();j++){
			state& c = v[i][j];
			if (c.l <= y && c.r >= x) ans.insert(c.val);
		}
		x = (dl[x] == -1 ? dr[x] : dl[x]);
		y = dr[y];
	}
	return ans.size();	
}
void init () {
	int cnt = 1, p = 3;
	memset(dl, -1, sizeof(dl));
	memset(dr, -1, sizeof(dr));
	dl[1] = 1; dr[1] = 2;
	for (int i = 2; i < M; i++) {
		if ((1<<cnt) == i) {
			cnt++;
			dl[i] = p++;
		}
		dr[i] = p++;
	}
}
int main () {
	init ();
	int order, d, x, y, val;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d", &order);
		if (order == 1) {
			scanf("%d%d%d%d", &d, &x, &y, &val);
			v[d].push_back(state(x, y, val));
		} else {
			scanf("%d%d", &d, &x);
			printf("%d\n", solve(d, x, x));
		}
	}
	return 0;
}
```

---

## 作者：Hades18 (赞：0)

首先先安利一发**[翻译](https://www.luogu.org/discuss/show/33341?page=1)**.

面对数据范围我们发现$m^2$的复杂度是能过的,所以我们可以考虑一下每一次询问暴力扫之前的修改,然后统计答案.

对于每次询问,询问的是子树,而修改的是同一深度的标号区间,所以我们需要知道询问的子树在这一深度所覆盖的标号区间,而这才是这一题的重点.

----------------

设子树的```root```为```(t,id)```,则```root```的右孩子(单一孩子)的标号为```(t,[1,id])```中```$2^k$```的个数加上id,当```id=$2^k$```时左孩子为右孩子的标号```-1```.

预处理出每一个深度的覆盖区间,然后判区间重叠就好了.

具体见代码：

-------------------------
```
#include<set>
#include<cstdio>
#define N 7005
//快读;
inline int read(){
	int x=0,f=0;
	register char ch=getchar();
	for(;ch<48||ch>57;ch=getchar())f|=ch=='-';
	for(;ch>47&&ch<58;ch=getchar())
	x=(x<<1)+(x<<3)+(ch^48);
	return f?~x+1:x;
}
using namespace std;set<int>s;
int t[N],l[N],r[N],x[N],pos[N][2],cnt;
int main()
{
	int n=read(),m=read();
	for(int i=0;i<m;++i)
	if(read()==1)t[++cnt]=read(),l[cnt]=read(),r[cnt]=read(),x[cnt]=read();//记录修改;
	else
	{
		int lvl=read();pos[lvl][1]=pos[lvl][0]=read();s.clear();
        //处理覆盖区间;
		for(int i=lvl;i<n;++i)
		{
			int k=pos[i][0],j=0,c=0;
			for(;k;k>>=1,++j)c+=k&1;
			pos[i+1][0]=pos[i][0]+j-(c==1);
			k=pos[i][1],j=0;
			for(;k;k>>=1,++j);
			pos[i+1][1]=pos[i][1]+j;
		}
        //线段覆盖;
        for(int i=1;i<=cnt;++i)
		if(t[i]>=lvl&&(l[i]<=pos[t[i]][0]&&pos[t[i]][0]<=r[i]||l[i]<=pos[t[i]][1]&&pos[t[i]][1]<=r[i]||pos[t[i]][0]<=l[i]&&r[i]<=pos[t[i]][1]))
		s.insert(x[i]);printf("%d\n",s.size());
	}
}
```

---

