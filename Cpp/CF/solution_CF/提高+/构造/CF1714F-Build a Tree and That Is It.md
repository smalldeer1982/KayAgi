# Build a Tree and That Is It

## 题目描述

# Build a Tree and That Is It


树是一个没有环的无向连通图，**注意**，在本题中，我们讨论的是无根树

现有四个整数 $ n, d_{12}, d_{23} $ 和 $ d_{31} $ . 构建一颗满足以下条件的树:

- 包含从 $ 1 $ 到 $ n $ 的 $n$ 个节点,
- 从节点 $ 1 $ 到节点 $ 2 $ 的距离（最短路的长度）为 $ d_{12} $ ,
- 从节点 $ 2 $ 到节点 $ 3 $ 的距离为 $ d_{23} $ ,
- 从节点 $ 3 $ 到节点 $ 1 $ 的距离为 $ d_{31} $ .

输出满足条件的任意一棵树；若不存在，请~~证明~~.

## 样例 #1

### 输入

```
9
5 1 2 1
5 2 2 2
5 2 2 3
5 2 2 4
5 3 2 3
4 2 1 1
4 3 1 1
4 1 2 3
7 1 4 1```

### 输出

```
YES
1 2
4 1
3 1
2 5
YES
4 3
2 5
1 5
5 3
NO
YES
2 4
4 1
2 5
5 3
YES
5 4
4 1
2 5
3 5
YES
2 3
3 4
1 3
NO
YES
4 3
1 2
2 4
NO```

# 题解

## 作者：Binary_Lee (赞：6)

## [题面传送门](https://www.luogu.com.cn/problem/CF1714F)

### 解决思路

题目中虽然说是无根树，但我们可以钦定这棵树的根为节点 $1$，方便构造，这是不
影响结果的。

以下记给定的三段长度为 $a,b,c$。

**先考虑无解的情况。**

- 首先，给出的三个距离，任意两者之和必须大于等于第三者，否则显然无解。

- 其次，用到的边数不能 $\ge n$。

- 最后，两个节点的 $\text{LCA}$ 到根节点的距离 (绿色) 是整数，两节点之间最短距离 (蓝色) 也是整数，而 $a+b+c$ 正好是蓝色绿色各算两次，所以 $a+b+c$ 必须是偶数。

![](https://cdn.luogu.com.cn/upload/image_hosting/4ultaizf.png)

**然后考虑如何构造。**

为了方便，我们钦定节点 $2$ 离根节点距离较小的一个。可以事先比较并做交换，输出时修改一下。

一种比较简单的想法：

给一组例子：

```
10 5 5 4
```

首先把节点 $2$ 和节点 $3$ 可以公共的部分输出。公共祖先数 (不包括节点 $1$ ) 可以这样
算: $(a+c-b)/2$（想一想为什么）。输出的 $now$（当前填充节点）应该从节点 $4$ 开始，$lst$（上一个节点）初始设为节点 $1$，之后每一次将 $lst$ 更新为 $now$，然后将 $now +1$。 

处理完会变成这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/2egsuf5j.png)

然后从当前扩展到的节点分别向两侧延伸，记已经输出的公共祖先数为 $cnt$，那么节点 $2$ 还需拓展的点数为 $a-cnt-1$，节点 $3$ 还需拓展的点数为 $b-(a-cnt)-1$。像之前一样分别向两边拓展即可。注意拓展节点 $2$ 之前先把 $lst$ 暂存下来，方便之后拓展节点 $3$  时将 $lst$ 归位。

处理完会变成这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/4udc6hmr.png)

最后还剩的点全部连到节点 $1$ 上即可（连其他地方也没事）。

所以这个样例最后一组可行的解就是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/q8agh2tf.png)

先给出这一部分的代码：

```cpp
int _1=2,_2=3;
if(a>c){
	swap(a,c);
	swap(_1,_2);
}
int lst=1,now=4,cnt=0;
for(int i=1;i<=(a+c-b)/2;i++){
	cout<<lst<<' '<<now<<endl;
	lst=now,now++,cnt++;
}
a-=cnt,c-=cnt;
int t1=lst;
for(int i=1;i<a;i++){
	cout<<lst<<' '<<now<<endl;
	lst=now,now++;
}
cout<<lst<<' '<<_1<<endl;
lst=t1;
for(int i=1;i<b-a;i++){
	cout<<lst<<' '<<now<<endl;
	lst=now,now++;
}
cout<<lst<<' '<<_2<<endl;
for(int i=now;i<=n;i++) cout<<1<<' '<<i<<endl;
```
 
然而这样写却 $\text{WA}$ 了。~~对照错误样例~~ 通过仔细思考，我们可以发现一种特殊情况，比如：

```
6 2 3 5
```

这时，以上的程序给出了一个离谱的错误答案。手玩发现，这种特殊情况是整棵树恰好为一条链：

![](https://cdn.luogu.com.cn/upload/image_hosting/8f1omkzz.png)

这时，较近的点为较远的点的祖先，也就是 $a+b=c$。

所以，只需要特判出来，按照链的特点，用类似方法构造即可。

### AC Code

```cpp
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false)
#define TIE cin.tie(0),cout.tie(0)
using namespace std;
int T,n,a,b,c,d1,d2,d3;
void solve(){
	cin>>n>>a>>b>>c;
	d1=(a+c-b)/2;
	d2=(a+b-c)/2;
	d3=(b+c-a)/2;
	if(d1<0||d2<0||d3<0||d1+d2+d3>=n||(a+b+c)%2){
		cout<<"NO"<<endl;
		return ;
	}
	cout<<"YES"<<endl;
	int _1=2,_2=3;
	if(a>c){
		swap(a,c);
		swap(_1,_2);
	}
	int lst=1,now=4,cnt=0;
	if(a+b==c){
		for(int i=1;i<a;i++){
			cout<<lst<<' '<<now<<endl;
			lst=now,now++;
		}
		cout<<lst<<' '<<_1<<endl;
		lst=_1;
		for(int i=1;i<b;i++){
			cout<<lst<<' '<<now<<endl;
			lst=now,now++;
		}
		cout<<lst<<' '<<_2<<endl;
	}
	else{
		for(int i=1;i<=(a+c-b)/2;i++){
			cout<<lst<<' '<<now<<endl;
			lst=now,now++,cnt++;
		}
		a-=cnt,c-=cnt;
		int t1=lst;
		for(int i=1;i<a;i++){
			cout<<lst<<' '<<now<<endl;
			lst=now,now++;
		}
		cout<<lst<<' '<<_1<<endl;
		lst=t1;
		for(int i=1;i<b-a;i++){
			cout<<lst<<' '<<now<<endl;
			lst=now,now++;
		}
		cout<<lst<<' '<<_2<<endl;
	}
	for(int i=now;i<=n;i++) cout<<1<<' '<<i<<endl;
}
int main(){
	IOS;TIE;
	cin>>T;
	while(T--) solve();
	return 0;
} 
```

---

## 作者：yingkeqian9217 (赞：4)

## 前言 & 前置芝士

~~这是我 A 的最快的蓝题。~~

菊花图：除了根节点外所有点最多都只有一个儿子的树。听起来很玄学是吧，上图。

![](https://cdn.luogu.com.cn/upload/image_hosting/02ms435x.png)

## 题目描述

树是一个没有环的无向连通图，**注意**，在本题中，我们讨论的是无根树。

现有四个整数 $ n, d_{12}, d_{23} $ 和 $ d_{31} $。 构建一颗满足以下条件的树:

- 包含从 $ 1 $ 到 $ n $ 的 $n$ 个节点。
- 从节点 $ 1 $ 到节点 $ 2 $ 的距离（最短路的长度）为 $ d_{12} $，
- 从节点 $ 2 $ 到节点 $ 3 $ 的距离为 $ d_{23} $。
- 从节点 $ 3 $ 到节点 $ 1 $ 的距离为 $ d_{31} $。

输出满足条件的任意一棵树；若不存在，请~~证明~~。

## 分析

看到一棵树，而且还限制最短路的长度，不难想到菊花图。因为在此图中，对于任意点 $x$ 和 $y$ 满足 $LCA(x,y)=rt$，它们的最短路长度就是 $d_x+d_y$，其中 $d$ 表示当前点距离菊花中心 $rt$ 的距离。通俗来说，就是不在同一条枝上的两点的最短路，必定经过中心 $rt$。

考虑构造出的树就是菊花图，那么可以得出一个显然的结论：

$\left\{\begin{matrix} d_{12} = d_1 + d_2\\ d_{13} = d_1 + d_3\\ d_{23} = d_2 + d_3\\ \end{matrix}\right.$

~~由小学数学~~，我们可以轻易算出 $d_1,d_2,d_3$，于是我们就可以初步画一个图。

![](https://cdn.luogu.com.cn/upload/image_hosting/nqckq8y2.png)

那么，我们如何求出 $rt$ 的值呢？显然，当存在 $d_i=0$ 时，点 $i$ 即为中心；否则我们任取一点，如 $n$ 作为 $rt$ 即可。

接下来问题就很简单了，我们只要把每一个 $d_i$ 遍历一遍，往里面塞一些点即可。具体在实现时，我们可以记录当前未用点为 $cnt$，初始为 4，遍历 $d_i$ 过程中累加即可。注意最后一步需要特判，即最后连向 $rt$ 的那条边，要保证 $i$ 不是 $rt$。

但是，我们现在只用了 $cnt-1$ 个点，剩下的点怎么办呢？为了保证最短路，我们只需要把它们直接连至 $rt$ 即可。

最后还有一个问题，那就是对无解的判断。不难发现，当 $d_i$ 不是非负整数时，就是无解。考虑当前构所需造总点数，可以算出是 $d_1+d_2+d_3+1$ 个，特判是否 $\le n$ 即可。

## Code
```
#include<bits/stdc++.h>
using namespace std;
int T,a[10];
void solve(){
	int n,x,y,z;
	scanf("%d%d%d%d",&n,&x,&y,&z);
	int rt=n,cnt=4;//初始化
	a[1]=(x+z-y)/2;
	a[2]=(x+y-z)/2;
	a[3]=(y+z-x)/2;//求解d数组
	if((x+y+z)%2!=0||a[1]<0||a[2]<0||a[3]<0||a[1]+a[2]+a[3]+1>n)
	 return void(puts("NO"));//特判无解
	puts("YES");
	for(int i=1;i<=3;i++) if(!a[i]) rt=i;//记录rt
	for(int i=1;i<=3;i++){
		int p=i;
		for(int j=1;j<a[i];j++)
		 printf("%d %d\n",p,cnt),p=cnt++;//先塞中间的点
		if(a[i]) printf("%d %d\n",p,rt);//特判末位
	}
	while(cnt<=n)//处理余下的点
	 if(cnt==rt) cnt++;//注意对子环的判断
	 else printf("%d %d\n",cnt++,rt);
}
int main(){
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：封禁用户 (赞：2)

这是我第一次独立想出蓝题，写一篇题解纪念下。

许多大佬讲的有些麻烦，在这里蒟蒻提供一下自己的思路。

首先我们发现 1 到 3 这 3 个点只有 2 种组合：

![](https://i.jpg.dog/3ecfcee9d65c7aac1810bc286bb6878b.png)

或者

![](https://i.jpg.dog/c6a54e4365f99452ad290500a6db6bb3.png)

其中第 2 种方法中的 4 为临时节点，它可以是任意的节点，它的存在只是为了连接另外 3 个节点。

我们不能构造出第 3 种方法，原因显然。

于是我们的思路就很简单了。我们有 3 个节点，考虑他们的 6 种排列（1，2，3）（1，3，2）（2，1，3）等等。

我们可以将这 6 种排列分别尝试 2 种方法，如果发现合法就输出。

对于多余节点你可以任意处理。我的做法是把所有的多余节点连在 1 节点上。

重点是判断 2 种方法的合法，我们只需要判断是否有足够的点来构造，以及构造出的树是否合法。

我的代码里用了很多宏定义，可读性较低，你可以着重看 try1 函数和 try2 函数对于构造合法性的判断。

以下是本人丑陋的 AC 代码。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define try_list int n, int x, int y, int z, int dxy, int dyz, int dzx
#define list_element n, x, y, z, dxy, dyz, dzx
#define list1 n, 1, 2, 3, d12, d23, d31
#define list2 n, 1, 3, 2, d31, d23, d12
#define list3 n, 2, 1, 3, d12, d31, d23
#define list4 n, 2, 3, 1, d23, d31, d12
#define list5 n, 3, 1, 2, d31, d12, d23
#define list6 n, 3, 2, 1, d23, d12, d31

void print(int u, int v, int d, int &node) {
    while (--d) {
        cout << u << " " << node << endl;
        u = node;
        node++;
    }
    cout << u << " " << v << endl;
}

void print(int &node, int n) {
    while (node <= n) cout << 1 << " " << (node++) << endl;
}

bool try1(try_list) {
    // x---4---z  (m = 4)
    //     |
    //     |
    //     y
    if (dxy + dyz - dzx > 0 && (dxy + dyz - dzx) % 2 == 0) {
        int dmy = (dxy + dyz - dzx) / 2;
        int dxm = dxy - dmy;
        int dmz = dyz - dmy;
        if (dxm >= 1 && dmz >= 1 && dmy + dxm + dmz + 1 <= n) {
            cout << "YES" << endl;
            int node = 5;
            print(x, 4, dxm, node);
            print(4, y, dmy, node);
            print(4, z, dmz, node);
            print(node, n);
            return true;
        }
    }
    return false;
}

bool try2(try_list) {
    // x---y---z
    if (dxy + dyz == dzx && dzx + 1 <= n) {
        cout << "YES" << endl;
        int node = 4;
        print(x, y, dxy, node);
        print(y, z, dyz, node);
        print(node, n);
        return true;
    }
    return false;
}

bool try_all(try_list) {
    if (try1(list_element)) return true;
    if (try2(list_element)) return true;
    return false;
}

void run() {
    int n, d12, d23, d31;
    cin >> n >> d12 >> d23 >> d31;
    if (try_all(list1)) return;
    if (try_all(list2)) return;
    if (try_all(list3)) return;
    if (try_all(list4)) return;
    if (try_all(list5)) return;
    if (try_all(list6)) return;
    cout << "NO" << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) run();
    return 0;
}
```

---

## 作者：Ender_hz (赞：2)

# 题意

给定 $4$ 个正整数 $n, d_{12}, d_{23}, d_{31}$，问能否构造一棵有 $n$ 个节点的无根树，编号分别为 $1, 2, \cdots, n$，满足节点 $1$ 与节点 $2$ 的距离为 $d_{12}$，节点 $2$ 与节点 $3$ 的距离为 $d_{23}$，节点 $3$ 到节点 $1$ 的距离为 $d_{31}$？

注意：每条边的边权均为 $1$ 。（感谢 @[cachejtt](https://www.luogu.com.cn/user/119707) 的提醒）

# 分析

题目说是无根树，我们不妨假设它有一个根节点，通过三条长度为 $d_1, d_2, d_3$ 的不相交的链分别连接节点 $1, 2, 3$（其中可能有一项为 $0$，此时该节点即为根节点）。

$d_1, d_2, d_3$ 可通过下列方程组求出：
$$
\begin{cases}
d_1+d_2=d_{12}\\d_2+d_3=d_{23}\\d_3+d_1=d_{31}
\end{cases}
$$
通过消元易得：
$$
\begin{cases}
d_1=\dfrac{d_{12}+d_{31}-d_{23}}2\\d_2=\dfrac{d_{12}+d_{23}-d_{31}}2\\d_3=\dfrac{d_{23}+d_{31}-d_{12}}2
\end{cases}
$$
注意判断 $d_1, d_2, d_3$ 的正负以及是否为整数。

构造完 $3$ 条链的树即为满足 $3$ 个节点间的距离条件的最小的树，此时判断节点数量与 $n$ 的大小关系：

+ 若节点数量 $<n$，则剩下的节点接在任意节点上均不会影响树的合法性；
+ 若节点数量 $=n$，则构造结束；
+ 若节点数量 $>n$，则构造失败。

每个节点只遍历一次，时间复杂度 $\mathcal O(n)$。

# 代码

```cpp
#include<iostream>
#define sfor(i, h, t) for(int i = (h); i <= (t); ++i)
using namespace std;
int T, N, d12, d23, d13;
int d[4], cnt, root;
signed main(void) {
    ios::sync_with_stdio(false);
    cin >> T;
    while(T--) {
        cin >> N >> d12 >> d23 >> d13;
        d[1] = (d12 + d13 - d23) >> 1;
        d[2] = (d12 + d23 - d13) >> 1;
        d[3] = (d13 + d23 - d12) >> 1;
        if(d[1] < 0 || d[2] < 0 || d[3] < 0 || d[1] + d[2] + d[3] + 1 > N || d12 + d23 + d13 & 1) {
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
        cnt = 3;
        root = 0;
        sfor(i, 1, 3)
            if(!d[i]) {
                root = i;
                break;
            }
        if(!root) {
            cnt = 4;
            root = 4;
        }
        sfor(k, 1, 3) {
            if(k != root) {
                cout << root << ' ';
                sfor(i, 1, d[k] - 1) {
                    ++cnt;
                    cout << cnt << '\n' << cnt << ' ';
                }
                cout << k << '\n';
            }
        }
        while(cnt < N)
            cout << "1 " << ++cnt << '\n';
    }
    return 0;
}
```



---

## 作者：happy_dengziyue (赞：1)

### 1 视频题解

![](bilibili:BV1Qg41117Qb)

### 2 思路

首先，假如真的有解，我们将 $1$ 定为根的话，设 $l$ 点为 $2$ 和 $3$ 点的最近公共祖先。以下请大家注意 $1$ 和 $l$ 的区别。

那么：

$$dis_{1,2}=dis_{1,l}+dis_{2,l}$$

$$dis_{2,3}=dis_{2,l}+dis_{3,l}$$

$$dis_{3,1}=dis_{3,l}+dis_{1,l}$$

那么：

$$dis_{1,2}+dis_{2,3}+dis_{3,1}=(dis_{1,l}+dis_{2,l}+dis_{3,l})\times2$$

我们可以发现，无论如何，$dis_{1,2}+dis{2,3}+dis{3,1}$ 为偶数。

我们还可以发现，从 $1$、$2$、$3$ 点到 $l$ 点的路径互不覆盖（指的是**边**不重叠），也就是说：

$$dis_{1,l}+dis_{2,l}+dis_{3,l}<n$$

即：

$$dis_{1,2}+dis_{2,3}+dis_{3,1}<n\times2$$

我们可以发现，$dis_{1,2}$、$dis_{2,3}$、$dis_{3,1}$ 的最大值要小于等于另外两个数之和。这是一个“三角形定理”。

如何在不排序的情况下判断呢？我们设 $dma=\max(dis_{1,2},dis_{2,3},dis_{3,1})$，$s=dis_{1,2}+dis_{2,3}+dis_{3,1}$。那么，$dma\times2\le s$。

满足上述条件就一定有解了。

我们可以发现，若 $dma\times2=s$，说明一个点在另两个点的路径上，找到中间点和两边的点即可模拟。

否则，我们也可以算出：

$$dis_{1,l}=\dfrac{s}{2}-dis_{2,3}$$

$$dis_{2,l}=\dfrac{s}{2}-dis_{3,1}$$

$$dis_{3,l}=\dfrac{s}{2}-dis_{1,2}$$

模拟即可。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define max_n 200000
int t;
int pi;
int n;
int d[6];
int askl(int x){
	--x;
	if(!x)x=3;
	return x;
}
int askr(int x){
	++x;
	if(x>3)x=1;
	return x;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1714F_2.in","r",stdin);
	freopen("CF1714F_2.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d%d",&n,d+1,d+2,d+3);
		int dma=max(d[1],max(d[2],d[3]));
		int s=d[1]+d[2]+d[3];
		if((dma<<1)>s||(s&1)||(s>>1)>=n){
			printf("NO\n");
			continue;
		}
		printf("YES\n");
		pi=3;
		if((dma<<1)==s){
			int x;
			if(d[1]==dma)x=1;
			if(d[2]==dma)x=2;
			if(d[3]==dma)x=3;
			int l=askl(x);
			int r=askr(x);
			if(d[l]>=2){
				printf("%d %d\n",x,++pi);
				for(int i=1;i<=d[l]-2;++i,++pi)printf("%d %d\n",pi,pi+1);
				printf("%d %d\n",pi,l);
			}
			else printf("%d %d\n",x,l);
			if(d[r]>=2){
				printf("%d %d\n",l,++pi);
				for(int i=1;i<=d[r]-2;++i,++pi)printf("%d %d\n",pi,pi+1);
				printf("%d %d\n",pi,r);
			}
			else printf("%d %d\n",l,r);
		}
		else{
			int dl1=(s>>1)-d[2];//1到lca(2,3)
			int dl2=(s>>1)-d[3];//lca(2,3)到2
			int dl3=(s>>1)-d[1];//lca(2,3)到3
			int lca;
			if(dl1>=2){
				printf("%d %d\n",1,++pi);
				for(int i=1;i<=dl1-1;++i,++pi)printf("%d %d\n",pi,pi+1);
				lca=pi;
			}
			else printf("%d %d\n",1,lca=++pi);
			if(dl2>=2){
				printf("%d %d\n",lca,++pi);
				for(int i=1;i<=dl2-2;++i,++pi)printf("%d %d\n",pi,pi+1);
				printf("%d %d\n",pi,2);
			}
			else printf("%d %d\n",lca,2);
			if(dl3>=2){
				printf("%d %d\n",lca,++pi);
				for(int i=1;i<=dl3-2;++i,++pi)printf("%d %d\n",pi,pi+1);
				printf("%d %d\n",pi,3);
			}
			else printf("%d %d\n",lca,3);
		}
		while((++pi)<=n)printf("%d %d\n",1,pi);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/82187134)

By **dengziyue**

---

## 作者：WaterSun (赞：0)

前言：鸣谢 Ender_hz 大佬提供的思路。

# 思路

由于题目中说这是一棵无根树，不太方便思考，于是，我们可以假装把这棵树看做有根树。

首先我们令 $d_1,d_2,d_3$ 分别表示从根节点到节点 $1,2,3$ 的长度（不算相交部分）。

那么我们可以得到下式：

$$
\left\{\begin{matrix}
d_{12} = d_1 + d_2\\
d_{13} = d_1 + d_3\\
d_{23} = d_2 + d_3\\
\end{matrix}\right.
$$

我们已知 $d_{12},d_{13},d_{23}$，那么我们尽可能的将 $d_1,d_2,d_3$ 用 $d_{12},d_{13},d_{23}$ 表示。

然后，根据将三式互相代入得：

$$
\left\{\begin{matrix}
d_1 = \frac{d_{12} + d_{13} - d_{23}}{2}\\
d_2 = \frac{d_{12} + d_{23} - d_{13}}{2}\\
d_3 = \frac{d_{13} + d_{23} - d_{12}}{2}\\
\end{matrix}\right.
$$

知道了上述式子，我们可以先来看一下输出 `NO` 的情况。

1. $d_{1} < 0 \operatorname{or} d_2 < 0 \operatorname{or} d_3 < 0$，一定无解。因为如果距离为负了一定不成立。

2. $d_1 + d_2 + d_3 \geq N$，一定无解。因为如果最短的距离之和（可以理解为最少需花费的节点数量减 $1$）大于了上限，一定无解。

3. $(d_{12} + d_{13} + d_{23}) \bmod 2 = 1$，一定无解。因为我们的 $d_1,d_2,d_3$ 一定是整数，如果它们三数相加不是 $2$ 的倍数，那么最后的 $d_1,d_2,d_3$ 一定不为整数。

后面我们直接挨着挨着加点即可。

需要注意的是，有可能建立完 $d_1 + d_2 + d_3$ 个节点后，没有花完 $N$ 个点，我们只需将剩下的点随便加到某一个节点之下即可。

# code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

int T,n,a,b,c,d;
int arr[15];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

int main(){
	T = read();
	while (T--){
		n = read();
		a = read();
		b = read();
		c = read();
		arr[1] = a + c - b >> 1;
		arr[2] = a + b - c >> 1;
		arr[3] = b + c - a >> 1;
		if (arr[1] < 0 ||  arr[2] < 0 || arr[3] < 0 || arr[1] + arr[2] + arr[3] >= n || a + b + c & 1) puts("NO");//判断无解 
		else{
			puts("YES");
			int idx = 3,r = 0;
			for (re int i = 1;i <= 3;i++){//找出一个根 
				if (!arr[i]){
					r = i;
					break;
				}
			}
			if (!r) r = idx = 4;//如果没找到直接随便认一个 
			for (re int i = 1;i <= 3;i++){
				if (i == r) continue;
				printf("%d ",r);//挨个加边 
				for (re int j = 1;j < arr[i];j++) printf("%d\n%d ",++idx,idx);
				printf("%d\n",i);
			}
			while (idx < n) printf("1 %d\n",++idx);//加剩下的点 
		}
	}
	return 0;
}
```

---

## 作者：Leasier (赞：0)

考虑 $d_{31} = d_{12} + d_{23}$ 的情况，显然可以构造如下的一棵树：

![](https://cdn.luogu.com.cn/upload/image_hosting/d3dmg59x.png)

其中 $x, y, z$ 均为一条直链。

$d_{12} = d_{23} + d_{31}$ 和 $d_{23} = d_{12} + d_{31}$ 的情况同理。

考虑 $d_{12} < d_{23} + d_{31}$ 的情况，显然可以构造如下的一棵树：

![](https://cdn.luogu.com.cn/upload/image_hosting/3evd4nzq.png)

其中 $x$ 为一个点，$y, z, w$ 均为一条直链。

现在考虑 $d_{1, x}, d_{2, x}, d_{3, x}$。

显然 $d_{3, x} = \frac{d_{13} + d_{23} - d_{12}}{2}$（当然我们也可以得到 $2 \not\mid d_{12} + d_{13} + d_{23}$ 时该情况不成立）。

从而，我们也可以得到 $d_{1, x} = d_{31} - d_{3, x}, d_{2, x} = d_{23} - d_{3, x}$。

当此时算出的 $d_{1, x}, d_{2, x}$ 存在一个 $\leq 0$ 或 $d_{1, x} + d_{2, x} + d_{3, x} \geq n$ 时该情况不成立。

有可能还会剩下一些点没用到，随意将其连成一条链并挂在上图任意一个点上就可以了。

$d_{31} < d_{12} + d_{23}$ 和 $d_{23} < d_{12} + d_{31}$ 的情况同理。

代码：
```cpp
#include <stdio.h>

int main(){
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++){
		int n, d12, d23, d31;
		scanf("%d %d %d %d", &n, &d12, &d23, &d31);
		if (d31 == d12 + d23){
			int pos = 3;
			printf("YES\n");
			if (d12 == 1){
				printf("1 2\n");
			} else {
				for (int j = 1, k = 1; j < d12; j++, k = pos){
					printf("%d %d\n", k, ++pos);
				}
				printf("%d 2\n", pos);
			}
			if (d23 == 1){
				printf("2 3\n");
			} else {
				for (int j = 1, k = 2; j < d23; j++, k = pos){
					printf("%d %d\n", k, ++pos);
				}
				printf("%d 3\n", pos);
			}
			pos++;
			for (int j = 2; pos <= n; j = pos++){
				printf("%d %d\n", j, pos);
			}
		} else if (d12 == d23 + d31){
			int pos = 3;
			printf("YES\n");
			if (d31 == 1){
				printf("1 3\n");
			} else {
				for (int j = 1, k = 1; j < d31; j++, k = pos){
					printf("%d %d\n", k, ++pos);
				}
				printf("%d 3\n", pos);
			}
			if (d23 == 1){
				printf("3 2\n");
			} else {
				for (int j = 1, k = 3; j < d23; j++, k = pos){
					printf("%d %d\n", k, ++pos);
				}
				printf("%d 2\n", pos);
			}
			pos++;
			for (int j = 3; pos <= n; j = pos++){
				printf("%d %d\n", j, pos);
			}
		} else if (d23 == d12 + d31){
			int pos = 3;
			printf("YES\n");
			if (d12 == 1){
				printf("2 1\n");
			} else {
				for (int j = 1, k = 2; j < d12; j++, k = pos){
					printf("%d %d\n", k, ++pos);
				}
				printf("%d 1\n", pos);
			}
			if (d31 == 1){
				printf("1 3\n");
			} else {
				for (int j = 1, k = 1; j < d31; j++, k = pos){
					printf("%d %d\n", k, ++pos);
				}
				printf("%d 3\n", pos);
			}
			pos++;
			for (int j = 1; pos <= n; j = pos++){
				printf("%d %d\n", j, pos);
			}
		} else if ((d12 + d23 + d31) % 2 != 0){
			printf("NO\n");
		} else {
			if (d12 < d31 + d23){
				int p = (d31 + d23 - d12) / 2, q = d31 - p, r = d23 - p;
				if (q > 0 && r > 0 && p + q + r < n){
					int pos = 3, centroid, k = 3;
					printf("YES\n");
					for (int j = 1; j <= p; j++, k = pos){
						printf("%d %d\n", k, ++pos);
					}
					centroid = k = pos;
					for (int j = 1; j < q; j++, k = pos){
						printf("%d %d\n", k, ++pos);
					}
					printf("%d 1\n", k);
					k = centroid;
					for (int j = 1; j < r; j++, k = pos){
						printf("%d %d\n", k, ++pos);
					}
					printf("%d 2\n", k);
					while (pos < n){
						printf("%d ", pos);
						printf("%d\n", ++pos);
					}
					continue;
				}
			}
			if (d31 < d12 + d23){
				int p = (d12 + d23 - d31) / 2, q = d12 - p, r = d23 - p;
				if (q > 0 && r > 0 && p + q + r < n){
					int pos = 3, centroid, k = 2;
					printf("YES\n");
					for (int j = 1; j <= p; j++, k = pos){
						printf("%d %d\n", k, ++pos);
					}
					centroid = k = pos;
					for (int j = 1; j < q; j++, k = pos){
						printf("%d %d\n", k, ++pos);
					}
					printf("%d 1\n", k);
					k = centroid;
					for (int j = 1; j < r; j++, k = pos){
						printf("%d %d\n", k, ++pos);
					}
					printf("%d 3\n", k);
					while (pos < n){
						printf("%d ", pos);
						printf("%d\n", ++pos);
					}
					continue;
				}
			}
			if (d23 < d12 + d31){
				int p = (d12 + d31 - d23) / 2, q = d12 - p, r = d31 - p;
				if (q > 0 && r > 0 && p + q + r < n){
					int pos = 3, centroid, k = 1;
					printf("YES\n");
					for (int j = 1; j <= p; j++, k = pos){
						printf("%d %d\n", k, ++pos);
					}
					centroid = k = pos;
					for (int j = 1; j < q; j++, k = pos){
						printf("%d %d\n", k, ++pos);
					}
					printf("%d 2\n", k);
					k = centroid;
					for (int j = 1; j < r; j++, k = pos){
						printf("%d %d\n", k, ++pos);
					}
					printf("%d 3\n", k);
					while (pos < n){
						printf("%d ", pos);
						printf("%d\n", ++pos);
					}
					continue;
				}
			}
			printf("NO\n");
		}
	}
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：0)

首先设 $x=d_{1,\operatorname{LCA}(2,3)},y=d_{2,\operatorname{LCA}(2,3)},z=d_{3,\operatorname{LCA}(2,3)}$，那么 $x+y=d_{1,2},x+z=d_{1,3},y+z=d_{2,3}$，然后解出 $x,y,z$，构造长度分别为 $x,y,z$ 的链即可。

多余的节点可以作为 $1$ 的其它儿子，这样就不会影响 $d_{1,3},d_{1,2},d_{2,3}$。

---

## 作者：EXODUS (赞：0)

# Part 1：前言
sto linyihdfj orz，完全没有想到那种解法。

很多人似乎看了这个题就跳了？好像没有那么难（虽然 G 更简单）。

接下来说说我的赛事想法

~~高度毒瘤代码警告~~

# Part 2：正文
无根树？那就把 $1$ 号节点当根！

注意到把一号节点当根还是有好处的。

- $d_{12}=dep_2$
- $d_{13}=dep_3$
- $d_{23}=(dep_2+dep_3)-2dep_{lca(2,3)}\rightarrow dep_{lca(2,3)}=\frac{dep_2+dep_3-d_{23}}{2}$

这里我没判负数，因为我的代码实现里有负数会让他一直死循环建边，所有节点都会被用完，~~然后就寄了~~。

首先判掉 $dep_{lca(2,3)}$ 不为整数的情况，然后建边 $1\rightarrow lca(2,3)$，$lca(2,3)\rightarrow 2$，$lca(2,3)\rightarrow 3$，点不足直接输出 "NO"，多的点都挂到 $1$ 号节点上就行了（我是新挂了一条链）。

注意可能会出现 $lca(2,3)=2\ or\ 3$ 的情况，特判即可。

代码略长，因为没写建链函数，但大部分是复制粘贴的，所以真实长度并没有很夸张。~~为了掩埋自己代码很长的事实~~，只给出了核心代码。

# Part 3：代码
```cpp
const int N=2e5+7;
int n,d23,d2,d3,dlca;
queue<int>q;
int cnt=0;
struct edge{
    int u,v;
}e[N];
int main(){
    int t=read();
    while(t--){
    	cnt=0;
        n=read(),d2=read(),d23=read(),d3=read();
        while(!q.empty())q.pop();
        for(int i=4;i<=n;i++)q.push(i);
        dlca=d2+d3-d23;
        if(dlca&1){
            puts("NO");
            continue;
        }else{
            dlca>>=1;d2-=dlca,d3-=dlca;int lst=1;
            //cout<<dlca<<endl;
            //3 is lca of(2,3)
            if(!d2){
                while(dlca!=1&&q.size()){
                    dlca--;
                    e[++cnt].u=lst;
                    lst=q.front();q.pop();
                    e[cnt].v=lst;
                }//cout<<q.size()<<endl;
                if(dlca!=1){
                    puts("NO");
                    continue;
                }
                e[++cnt].u=lst;
                e[cnt].v=2;
                lst=2;
                while(d3!=1&&q.size()){
                    d3--;
                    e[++cnt].u=lst;
                    lst=q.front();q.pop();
                    e[cnt].v=lst;
                }
                if(d3!=1){
                    puts("NO");
                    continue;
                }
                e[++cnt].u=lst;
                e[cnt].v=3;
            }else if(!d3){
                while(dlca!=1&&q.size()){
                    dlca--;
                    e[++cnt].u=lst;
                    lst=q.front();q.pop();
                    e[cnt].v=lst;
                }
                if(dlca!=1){
                    puts("NO");
                    continue;
                }
                e[++cnt].u=lst;
                e[cnt].v=3;
                lst=3;
                while(d2!=1&&q.size()){
                    d2--;
                    e[++cnt].u=lst;
                    lst=q.front();q.pop();
                    e[cnt].v=lst;
                }
                if(d2!=1){
                    puts("NO");
                    continue;
                }
                e[++cnt].u=lst;
                e[cnt].v=2;
                lst=2;
            }else{
                while(dlca&&q.size()){
                    dlca--;
                    e[++cnt].u=lst;
                    lst=q.front();q.pop();
                    e[cnt].v=lst;
                }
                if(dlca){puts("NO");continue;}
                int cpy=lst;
                while(d2!=1&&q.size()){
                    d2--;
                    e[++cnt].u=lst;
                    lst=q.front();q.pop();
                    e[cnt].v=lst;
                }
                if(d2!=1){
                    puts("NO");
                    continue;
                }
                e[++cnt].u=lst;
                e[cnt].v=2;
                lst=cpy;
                while(d3!=1&&q.size()){
                    d3--;
                    e[++cnt].u=lst;
                    lst=q.front();q.pop();
                    e[cnt].v=lst;
                }
                if(d3!=1){
                    puts("NO");
                    continue;
                }
                e[++cnt].u=lst;
                e[cnt].v=3;
                lst=cpy;
            }
            puts("YES");
            lst=1;
            while(!q.empty()){
                e[++cnt].u=lst;
                lst=q.front();q.pop();
                e[cnt].v=lst;
            }
            for(int i=1;i<=cnt;i++){
                printf("%d %d\n",e[i].u,e[i].v);
            }
        }
    }
    return 0;
}
```
# Part 4：后文
点赞再走吧（可怜

---

## 作者：linyihdfj (赞：0)

## F.Build a Tree and That Is It
### 题目描述：
[原题面](https://codeforc.es/contest/1714/problem/F)
### 题目分析：
赛时的时候可能看见构造一棵树很多人就直接跳了，但是其实一点也不难。

我们考虑题目就给了四个限制：边数、$1$ 和 $2$ 和 $3$ 相互的距离。

那么我们显然最难满足的就是距离的限制，那么我们就考虑如何去搞。虽然题目说无根树，但是我们构造按有根树更好弄。

我们会发现一个性质，如果满足 $dis_{a,b} + dis_{b,c} = dis_{a,c}$，那么意味着 $b$ 就是 $a,c$ 两点形成的链的中间节点。

所以根据这个性质就直接以 $b$ 为根，向两边延伸，如果距离够了就插入 $a,c$ 节点，不够就插入没用的节点。这里也就是可以得到判负的一个条件：点的数量不够。

考虑一个如果不存在 $dis_{a,b} + dis_{b,c} = dis_{a,c}$，那么意味着什么。那么就是 $a,b,c$ 一定是以另一个点为根的树延伸出去的三条不同链上的点，而且我们也肯定能够解出来他们的距离，也就是解下列这个方程组：

$$
\begin{cases}
dis_1 + dis_2 = d_{12} \\
dis_1 + dis_3 = d_{31} \\
dis_2 + dis_3 = d_{23} \\
\end{cases}
$$

$dis_i$ 代表从根到 $i$ 的距离，这样也就是上面的同理，从根延伸，到了距离就把当前点插入然后继续下一条链。这里又是一些的判负条件也就是 $dis_1,dis_2,dis_3$ 的和、正负的限制。

注意：我们可能存在最后没插完所有节点，那么也好弄，直接全部挂到指定的根上就好了。

### 代码详解：
```cpp
#include<bits/stdc++.h>
using namespace std;
int dis[4];
void build(int root,int to,int dis,int &now){  //以 now 为根建一条到 to 的边权为 dis 的边 
	int last = root,now_dis = 1;
	while(now_dis <= dis){
		if(now_dis == dis){
			printf("%d %d\n",last,to);
			break;
		}
		printf("%d %d\n",last,now);
		last=now;now++;now_dis++;
	}
}
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,d12,d23,d13;
		cin>>n>>d12>>d23>>d13;
		int root = 0;
		if(d12 == d23 + d13)
			root = 3;
		else if(d23 == d12 + d13)
			root = 1;
		else if(d13 == d12 + d23)
			root = 2;
		else	
			root = 4;
		if(root == 4 && n == 3){
			printf("NO\n");continue;
		}
		if((root == 1 && d23 > n-1) || (root == 3 && d12 > n-1) || (root == 2 && d13 > n-1)){
			printf("NO\n");	continue;
		}
		if(root == 4){
			dis[1] = d13 + d23 + d12 - 2 * d23;
			dis[2] = d13 + d23 + d12 - 2 * d13;
			dis[3] = d13 + d23 + d12 - 2 * d12;
			if(dis[1] % 2!= 0 || dis[2] % 2 != 0 || dis[3] % 2 != 0 ||dis[1] <= 0 || dis[2] <= 0 || dis[3] <= 0){
				printf("NO\n");
				continue; 
			}
			dis[1]/=2;dis[2]/=2;dis[3]/=2;
			if(dis[1] + dis[2] + dis[3] > n-1){
				printf("NO\n");
				continue;
			}
			int now = 5;  //now 就是指的我们现在使用的没有什么用的节点 
			printf("YES\n");
			build(4,1,dis[1],now);
			build(4,2,dis[2],now);
			build(4,3,dis[3],now);
			while(now <= n)	printf("%d %d\n",4,now++);
		}
		else{
			printf("YES\n");
			int now = 4;
			if(root == 1){
				build(1,2,d12,now);
				build(1,3,d13,now);
				while(now<=n) 	printf("%d %d\n",1,now++);
			}
			else if(root == 2){
				build(2,1,d12,now);
				build(2,3,d23,now);
				while(now<=n)	printf("%d %d\n",2,now++); 
			}
			else if(root == 3){
				build(3,1,d13,now);
				build(3,2,d23,now);
				while(now<=n)	printf("%d %d\n",3,now++);
			}
		}
	} 
	return 0;
}
```

---

## 作者：D2T1 (赞：0)

## F. Build a Tree and That Is It

全场最难题。

如果有解，$1-2,2-3,3-1$ 三条路径只有如下四种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/1c3dvu5b.png)

接下来具体考虑：

- 若 $d_{12},d_{23},d_{31}$ 其一大于另两数之和，无解。
- 可以发现四种解中每条路径都在 $d_{12},d_{23},d_{31}$ 中出现两次，所以若 $d_{12}+d_{23}+d_{31}$ 为奇数，无解。
- 若 $d_{12}+d_{23}+d_{31} > 2n-2$，无解。
- 若 $d_{12},d_{23},d_{31}$ 其一等于另两数之和，分情况构造左上、左下、右上三种情况。

否则设 $1,2,3$ 到中间节点 $X$ 的三条路径长度分别为 $x,y,z$，可以列出方程组：

$$\begin{cases}x+y=d_{12}\\y+z=d_{23}\\z+x=d_{31}\end{cases}$$

解得

$$\begin{cases}x=(d_{12}-d_{23}+d_{31})\div2\\y=(d_{23}-d_{31}+d_{12})\div2\\z=(d_{31}-d_{12}+d_{23})\div2\end{cases}$$

此时如果 $x,y,z$ 中不全是整数，无解。否则按照右下图构造即可。

考场代码，很丑。

```cpp
#define multiple_test_cases

const int N = 2e5 + 10;
int n, d12, d23, d31, fa[N];

void build(int x, int l, int r, int xl, int xr){
	stack<int> st;
	st.push(x);
	int tmp = 4;
	for(int i = 1; i < xl; ++ i){
		st.push(tmp);
		++ tmp;
	}
	st.push(l);
	while(!st.empty()){
		int x = st.top();
		st.pop();
		if(!st.empty()) fa[x] = st.top();
	}
	st.push(x);
	for(int i = 1; i < xr; ++ i){
		st.push(tmp);
		++ tmp;
	}
	st.push(r);
	while(!st.empty()){
		int x = st.top();
		st.pop();
		if(!st.empty()) fa[x] = st.top();
	}
	for(int i = tmp; i <= n; ++ i){
		fa[i] = 1;
	}
}
void buildd(int x, int y, int z){
	stack<int> st;
	st.push(4);
	int tmp = 5;
	for(int i = 1; i < x; ++ i){
		st.push(tmp);
		++ tmp;
	}
	st.push(1);
	while(!st.empty()){
		int ww = st.top();
		st.pop();
		if(!st.empty()) fa[ww] = st.top();
	}
	st.push(4);
	for(int i = 1; i < y; ++ i){
		st.push(tmp);
		++ tmp;
	}
	st.push(2);
	while(!st.empty()){
		int ww = st.top();
		st.pop();
		if(!st.empty()) fa[ww] = st.top();
	}
	st.push(4);
	for(int i = 1; i < z; ++ i){
		st.push(tmp);
		++ tmp;
	}
	st.push(3);
	while(!st.empty()){
		int ww = st.top();
		st.pop();
		if(!st.empty()) fa[ww] = st.top();
	}
	for(int i = tmp; i <= n; ++ i){
		fa[i] = 1;
	}
}

void solve(){
	n = rdi;
	d12 = rdi;
	d23 = rdi;
	d31 = rdi;
	if((d12 + d23 + d31) & 1){
		puts("NO");
	} else if((d12 + d23 + d31) > n+n-2){
		puts("NO");
	} else {
		if(d12 == d23 + d31){
			build(3, 1, 2, d31, d23);
		} else if(d23 == d12 + d31){
			build(1, 2, 3, d12, d31);
		} else if(d31 == d12 + d23){
			build(2, 1, 3, d12, d23);
		} else {
			int x = d12 - d23 + d31;
            int y = d23 - d31 + d12;
            int z = d31 - d12 + d23;
            if((x&1) || (y&1) || (z&1) || x<0 || y<0 || z<0){
                puts("NO");
                return;
            } else {
                x >>= 1;
                y >>= 1;
                z >>= 1;
                buildd(x, y, z);
            }
		}
        puts("YES");
		for(int i = 1; i <= n; ++ i){
			if(fa[i]){
				write(i);
				writen(fa[i]);
                fa[i] = 0;
			}
		}
	}
}
```

---

