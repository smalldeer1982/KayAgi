# [NordicOI 2025] 时之预言 / Xoracle

## 题目背景

目前本题交互库有误。

## 题目描述

**这是一道交互题。**

很久以前，在北欧诸国的中心地带，有一位名叫罗尼的勇敢战士。罗尼以其无畏的勇气和敏锐的头脑闻名，常常能解开连最睿智的贤者都束手无策的谜题。有一天，罗尼被召集到一片古老的森林，那里屹立着一棵神秘的树。这棵树非同寻常——它完全隐形，其节点和分支对凡人之眼不可见。树的每个节点上都居住着一位古老的精灵，而每个节点的度数（degree）是理解树结构的关键。

王国的预言者，被称为**神秘树预言者**（Xoracle），是一个强大的存在，但它只能回答一种类型的问题： 「告诉我节点 A 和节点 B 的度数的按位异或结果。」

凭借这些神秘的信息，罗尼必须推导出树中所有 $N$ 个节点的度数，以征服古老的精灵并揭开树的秘密。然而，神秘树预言者最多只会回答 $Q$ 次询问，之后便会永远封存其智慧。

罗尼的任务是利用神秘树预言者的回答，确定这棵隐形树中所有节点的度数。这棵树有 $N$ 个节点和 $N-1$ 条边，是连通的，也就是说，任意一对节点之间都存在路径。节点的度数是指与该节点相连的边的数量。通过策略性地选择节点对并解读它们度数的按位异或结果，罗尼希望能重构树中所有节点的度数。

## 交互方式

你的程序首先需要读取一行输入，包含两个空格分隔的整数 $N$ 和 $Q$，分别表示树中的节点数量和你最多可以向神秘树预言者提出的询问次数。树的节点编号从 $1$ 到 $N$。

接下来，你的程序可以进行最多 $Q$ 次询问。要提出一个询问，你的程序需要输出一行，格式为 `? i j`，其中 $1 \leq i, j \leq N$。评测程序随后会返回一行，包含一个数字 $x$，其中 $x=\operatorname{deg}(i) \oplus \operatorname{deg}(j)$。这里 $\operatorname{deg}(x)$ 表示节点 $x$ 的度数，$\oplus$ 表示按位异或运算。

两个整数 $a$ 和 $b$ 的按位异或结果是通过查看它们的二进制表示计算出来的。第 $i$ 位的结果为 $1$，当且仅当 $a$ 或 $b$ 的第 $i$ 位有且仅有一个为 $1$。在 C++ 和 Python 中，这一运算符均为 ^。

在完成询问后，你的程序必须输出所有节点的度数。输出的方式是：另起一行，输出 !，后跟一个空格和 $N$ 个空格分隔的整数，表示所有 $N$ 个节点的度数（顺序不限）。

输出度数的操作不会计入你的程序允许的询问次数。

为了接收询问的答案并在最后提交度数，你的程序需要刷新输出缓冲区。可以通过以下方式实现：

- C++：`std::cout << std::endl;`
- Python：`print("", flush=True)`



## 说明/提示

【样例解释】

#### 样例 $1$

请观察图 1 中所示的树。

以下是你与评测程序的交互过程，其中 > 表示评测程序的输出，< 表示你的程序的输出。


- 首先，输入提供 $N$ 和 $Q$ 的值。
- 接着，你对节点 $2$ 和 $4$ 提出询问，得到结果 $0$。
- 然后，你对节点 $4$ 和 $1$ 提出询问，得到结果 $2$。
- 接着，你对节点 $3$ 和 $3$ 提出询问，得到结果 $0$。
- 最后，你的程序输出树的度数为 $1,3,1,1$，这是正确的。（注意，度数的输出顺序可以是任意的。）

![](https://cdn.luogu.com.cn/upload/image_hosting/dgdkk6q8.png)

#### 样例 $2$：

请观察图 2 中所示的树。

以下是你与评测程序的交互过程，其中 > 表示评测程序的输出，< 表示你的程序的输出。

![](https://cdn.luogu.com.cn/upload/image_hosting/pft1e2nv.png)

**注意**：样例中给出的询问不一定能保证推导出正确的答案。

【数据范围与约定】

对于所有数据，满足：

- $2 \leq N \leq 10^{5}$。

详细子任务附加限制及分值如下表所示：

| 子任务编号 | 分值 | 附加限制 |
| :-----------: | :-----------: | :-----------: |
| $1$ | $8$ |  任意节点的度数最大为 $3$，且树中至少存在度数为 $1$、$2$ 和 $3$ 的节点。$N\le 1000,Q=N-1$ |
| $2$ |  $5$|  任意节点的度数最大为 $4$，且树中至少出现 $4$ 种可能度数中的 $3$ 种。$N\le 1000,Q=N-1$  |
| $3$ |  $9$|$Q=N^2,N\le 300$ |
|$4$  |  $11$|$Q=35000,N\le 1000$ |
| $5$ |  $24$|$Q=N-1,N\le 1000$ |
|$6$  | $43$ |$Q=N-1$ |


## 样例 #1

### 输入

```
4 3
< ? 2 4
0
< ? 4 1
2
< ? 3 3
0
< ! 1 3 1 1```

### 输出

```
```

## 样例 #2

### 输入

```
5 4
< ? 1 2
3
< ? 1 3
1
< ? 2 3
2
< ? 1 4
3
< ! 3 1 1 1 2```

### 输出

```
```

# 题解

## 作者：xxr___ (赞：2)

简单题，但是有坑。

首先根据异或的性质，一个定值 $x$ 如果存在一个数 $y$ 使得 $x\oplus z = y$ 那么这个 $z$ 是唯一的。

那么我们可以考虑枚举 $1$ 的度数，然后询问 $deg_1\oplus deg_i,i\ne 1$ 的值就能推出其他点的度数，因为一个树的度数只和是 $2\times n - 2$ 的所以只需要判断一下就行，这样就是 $O(n^2)$ 的做法。

发现异或实际上就是二进制的某一个两者只有其中一种是 `1` 的时候才会有贡献，所以可以考虑把 $deg_1\oplus deg_i$ 的值的二进制下每一位是 `0` 是 `1` 的数量记录下来，然后询问直接枚举位数就行，这样就是 $O(n\log n)$ 的了。

细节，由于度数不能是 $0$ 所以你枚举的度数不能存在一个 $i$ 满足 $deg_1\oplus deg_i = deg_1$。

代码：
```cpp
#include<iostream>

const int N = 100005;
int n,q,xo[N],t[22],p[22];
bool vs[N << 3];
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cin >> n >> q;
	for(int i = 2;i <= n; ++i){
		std::cout << "? "<< 1 <<' '<< i << '\n';
		std::cout.flush();
		std::cin >> xo[i];
		for(int j = 0;j < 21; ++j){
			if(xo[i] >> j & 1){
				++ t[j];
			}else{
				++ p[j];
			}
		}
		vs[xo[i]] = 1;
	}
	for(int i = 1;i < n; ++i){
		int ans = i;
		for(int j = 0;j < 21; ++j){
			if(!(i >> j & 1)){
				ans += t[j] * (1 << j);
			}else{
				ans += p[j] * (1 << j);
			}
		}
		if(ans == 2 * n - 2 && !vs[i]){
			std::cout << "! ";
			std::cout.flush();
			std::cout << i << ' ';
			for(int j = 2;j <= n; ++j){
				std::cout << (i ^ xo[j]) << ' ';
			}
			std::cout.flush();
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：伊地知虹夏 (赞：2)

$\mathcal O(n)$ 做法申请出战！！！

首先这个交互是假的，我们考虑对 $2\le i \le n$ 求出 $a_i = d_1 \oplus d_i$。

容易验证这个度数序列合法的充要条件是 $\sum d_i = 2n - 2$ 且 $d_i > 0$。

考虑只有 $\mathcal O(\sqrt n)$ 种不同的度数，我们枚举 $d_1$ 就可以得到一个 $\mathcal O(n\sqrt n)$ 的做法。

注意到度数序列中至少有一个 $1$，那么合法的 $d_1$ 一定是某个 $d_i \oplus 1$，那么我们只要枚举这 $\mathcal O(\sqrt n)$ 种 $d_1$，配合桶排可以做到 $\mathcal O(n)$！

---

## 作者：XZhuRen (赞：1)

异或有自反性，询问是任意的，把所有节点跟 $1$ 拉出来询问一遍即可。

考虑判定，充要条件即 $\sum_{u\in [1,n]} deg(u)=n\times 2-2$ 且$\forall deg(u)\not= 0$。

严谨的做法是找众数之后枚举众数的度数暴力，复杂度 $\mathcal{O}(n\sqrt{n})$。

然而暴力也可以过，复杂度貌似正确。

没判 $deg()\not=0$ 也太奶了。

---

## 作者：_Ch1F4N_ (赞：0)

简单题。

考虑什么样的度数序列合法，由 Prüfer 序列不难发现，只要 $d_i > 0$ 且 $\sum d_i = 2 \times (n-1)$ 就合法。

考虑把异或关系问出来，也就是问出 $f_i = d_i \oplus d_1$。

注意到树一定有叶子，枚举一个一度点 $u$，那么实际度数序列就是 $f_i \oplus (f_u \oplus 1)$，判断是否存在 $0$ 度点可以直接用桶记录 $f_i = x$ 的点数量，判断和是否为 $2 \times (n-1)$ 可以拆二进制位算贡献。

总时间复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+114;
int ty[maxn][20];
int n,q;
int cnt[20];
int d[maxn];
map<int,int> vis;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>q;
    d[1]=0;
    vis[d[1]]=1;
    for(int i=2;i<=n;i++){
        cout<<"? "<<1<<" "<<i<<endl;
        int x;
        cin>>x;
        d[i]=x;
        vis[d[i]]=1;
        for(int j=0;j<20;j++){
            if((1<<j)&x) ty[i][j]=1,cnt[j]++;
        }
    }
    for(int i=1;i<=n;i++){
        if(vis[d[i]^1]==1) continue;
        long long sum=0;
        for(int j=0;j<20;j++){
            if(ty[i][j]==0){
                if(j==0) sum+=1ll*(n-cnt[j])*(1<<j);
                else sum+=1ll*cnt[j]*(1<<j);
            }else{
                if(j==0) sum+=1ll*cnt[j]*(1<<j);
                else sum+=1ll*(n-cnt[j])*(1<<j);
            }
        }
        if(sum==2*(n-1)){
            int del=d[i]^1;
            cout<<"! ";
            for(int j=1;j<=n;j++) cout<<(del^d[j])<<' ';
            cout<<endl;
            return 0;
        }
    }
    return 0;
}
```

---

## 作者：Acit (赞：0)

感觉不是很难。

**思路**

$N-1$ 次查询只需保证能求出任意两节点度数异或值即可，为方便起见，我们令第 $i$ 次查询询问了点 $i$ 和 $i+1$，这样任意两点度数异或值变成了一个区间异或值，线段树求解即可。

设得到的答案依次为 $a_{1}$ 到 $a_{N-1}$，记 $a$ 的异或前缀和数组为 $s$，两点 $i,j$ 度数相同当且仅当 $s_{i-1}=s_{j-1}$，扫一遍 $s$，用并查集维护度数相同的点。

如何构造答案呢？注意到如果一种度数的点最多，那么这些点的度只可能为 $1$ 或 $2$（从平均度数的角度考虑，证明不难）。又因为所有不同度数种类之和为 $O(\sqrt{N})$ 级别，确定一种答案后可以直接暴力枚举两种不同度数进行检查，所以解法呼之欲出：确定最多的度数为 $1$ 还是 $2$ 后暴力检查，合法的情况输出即可。

注意检查时要看每个点的度数是否等于零或大于等于 $N$，不然会挂三个点。

**Code**


```cpp
#include<bits/stdc++.h>
#define forr(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int N=1e5+10;
int n,q,s[N],tree[N<<2],f[N],s1[N],ans[N];
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
vector<int> e[N],cnt[N];
#define ls k<<1
#define rs k<<1|1
#define mid ((l+r)>>1)
void build(int k,int l,int r){
	if(l==r)return tree[k]=s[l],void();
	build(ls,l,mid);build(rs,mid+1,r);
	tree[k]=tree[ls]^tree[rs];
}
int ask(int k,int l,int r,int x,int y){
	if(x>r||y<l)return 0;
	if(x<=l&&r<=y)return tree[k];
	return ask(ls,l,mid,x,y)^ask(rs,mid+1,r,x,y);
}
int getxor(int x,int y){
	if(x>y)swap(x,y);
	return ask(1,1,n-1,x,y-1);//注意s记录的是相邻两项异或值，右界为y-1
}
void merge(int x,int y){//x->y
	int fx=find(x),fy=find(y);
	if(fx!=fy)f[fx]=fy;
}
void output(){
	cout<<"! ";
	forr(i,1,n)cout<<ans[f[i]]<<' ';
}
int tp[N],tt;
bool check(){
	forr(i,1,tt){
		forr(j,i+1,tt){
			if(getxor(e[tp[i]][0],e[tp[j]][0])!=(ans[e[tp[i]][0]]^ans[e[tp[j]][0]])){
				return 0;
			}
		}
	}
	int sum=0;
	forr(i,1,n){
		sum+=ans[f[i]];
		if(ans[f[i]]==0||ans[f[i]]>=n)return 0;//注意检查度数
	}
	if(sum!=2*n-2)return 0;
	return 1;
}
signed main() {
	ios::sync_with_stdio(0);
	cin>>n>>q;
	forr(i,1,n)f[i]=i;
	forr(i,1,n-1){
		cout<<"? "<<i<<' '<<i+1<<endl;
		cin>>s[i];s1[i]=s[i];
	}
	build(1,1,n-1);
	forr(i,1,n-1)s1[i]=s1[i-1]^s[i],cnt[s1[i]].push_back(i);//异或前缀和以及记录每种s1[i]对应的i
	forr(i,1,n-1){
		if(f[i]!=i)continue;
		//f[i]!=i 说明当前节点已经被并到别的节点上去了，此时不用扫描
		for(auto j : cnt[s1[i-1]]){
			if(j>=i)merge(j+1,i);
		}
	}
	forr(i,1,n)e[f[i]].push_back(i);
	int mx=0,pl=0;
	forr(i,1,n){
		int u=e[i].size();
		if(u>mx)mx=u,pl=i;
		if(u>0)tp[++tt]=i;
		//寻找最多的度数和记录所有度数
	}
	ans[pl]=1;//最多度数是1
	forr(i,1,n){
		if(e[i].size()>0&&i!=pl){
			ans[i]=getxor(e[i][0],e[pl][0])^1;
			//求出两种度数异或值后可直接计算答案
		}
	}
	if(check()){
		output();
		return 0;
	}
	ans[pl]=2;//最多度数是2
	forr(i,1,n){
		if(e[i].size()>0&&i!=pl){
			ans[i]=getxor(e[i][0],e[pl][0])^2;
		}
	}
	if(check()){
		output();
		return 0;
	}
	return 0;
}
```

---

