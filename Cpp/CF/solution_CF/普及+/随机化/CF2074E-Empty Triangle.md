# Empty Triangle

## 题目描述

这是一道交互题。

粉色士兵们向你隐藏了 $n$ 个（$3 \le n \le 1500$）固定点 $(x_1, y_1), (x_2, y_2), \ldots, (x_n, y_n)$，其坐标未给出。已知任意两点坐标不同，且任意三点不[共线](https://en.wikipedia.org/wiki/Collinearity)。

你可以向主持人（Frontman）询问三个不同的下标 $i$、$j$、$k$。随后，主持人会绘制由点 $(x_i, y_i)$、$(x_j, y_j)$、$(x_k, y_k)$ 构成的三角形，并按以下规则回应：

- 若至少有一个隐藏点位于三角形内部，主持人会返回其中一个这样的点的下标。注意，若有多个这样的点，主持人可以任意选择其中一个返回。
- 否则，主持人返回 $0$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2074E/e516ed9e8799abe3210fe85d082a2aa0f40e533f.png)  
你的目标是找到一个不包含其他隐藏点的三角形（如图中蓝色三角形所示）。你最多可以使用 $\mathbf{75}$ 次询问，找到由三个点构成的、内部不含其他隐藏点的任意三角形。

注意：主持人可能在选择返回的点时具有自适应性。换言之，返回点的选择可能受到多种因素影响（包括但不限于点的排列和之前的询问）。但需注意，点的序列永远不会被改变。

本题禁用 hack。你的解法将在恰好 $\mathbf{35}$ 个输入文件（包括示例输入）上进行评测。

## 说明/提示

第一个测试用例中的点为 $(3,0),(0,3),(5,2),(3,1),(2,2),(4,4)$。

三次询问对应的三角形如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2074E/e516ed9e8799abe3210fe85d082a2aa0f40e533f.png)  

可以看到，由 $(0,3)$、$(2,2)$、$(4,4)$ 构成的三角形内部不含其他隐藏点，因此是一个有效答案。

注意：交互示例仅展示合法的交互流程，不一定是实际响应。例如，当查询 "? 1 2 3" 时，主持人可能返回 $4$。但由于主持人不会改变点的序列，因此不会对同一查询返回 $6$。

第二个测试用例中仅有 $3$ 个点。因此，由这三点构成的唯一三角形内部不含其他隐藏点。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
2
6

5

4

0

3```

### 输出

```
? 1 2 3

? 1 5 3

? 2 5 6

! 2 5 6

! 1 2 3```

# 题解

## 作者：Magus (赞：1)

## 前言

Worst E ever. I appreciate that the author thought of such a creative idea but still Im not conviced this was a good E. —— 摘自[比赛公告](https://codeforces.com/blog/entry/140540)里 TiwoeeM 的回复。

## 题解

我们定义所选的三个点为 $x,y,z$。

读完题可以很自然想到，如果这三个点组成的三角形里面有其他的点，那就把 $x$ 换成所给你的那个点 $p$，最坏情况要换 $1497$ 次，直接爆了。

尝试不只换 $x$，**观察到本题禁用 hack**，所以我们将选择权交给随机数，然后你就会惊讶地发现这是正解。

证明：

我们设所选三角形内隐藏点个数为 $c$，根据抽屉原理，$x,y,z$ 三个点与 $p$ 组成的三个三角形中一定有一个三角形包含的点数是 $\leq \frac{c-1}{3}$ 的，取到这样的点的概率为 $\frac{1}{3}$，期望 $25$ 次，可以通过。

其实真正出错的概率比这个要小非常多，大约 $1.8 \times 10^{-20}$（参考官解），我也不知道为啥，有懂的大佬恳请在该题解下面回复。

```cpp
signed main()
{
	srand(time(0));
	cin>>t;
	while(t--)
	{
		cin>>n;
		x=1,y=2,z=3;
		while(1)
		{
			cout<<"? "<<x<<" "<<y<<" "<<z<<"\n";
			cin>>ans;
			if(!ans)
			{
				cout<<"! "<<x<<" "<<y<<" "<<z<<"\n";
				break;
			}
			else
			{
				res=rand()%3+1;
				if(res==1)
				{
					x=ans;
				}
				if(res==2)
				{
					y=ans;
				}
				if(res==3)
				{
					z=ans;
				}
			}
			fflush(stdout);				
		}
	}
	return 0;
}
```

---

## 作者：lw393 (赞：1)

这题比较的扯。我其实也不知道我怎么就赛时秒了正解的。

发现查询次数较 $\log_3^2 n$ 较为拟合（实际上并非如此）。

我们假设上一次查询的三元点对为 $(i,j,k)$。若交互库给出的结果是 $0$ 的话，就直接输出 $(i,j,k)$ 即可。若是 $p$ 呢？是不是卡在这了？

如果一直将 $k$ 替换成 $p$，脑海中浮现出来了这种画面：

![](https://cdn.luogu.com.cn/upload/image_hosting/udayue4q.png)

一下子就把贪心的想法磨灭掉了。那如何换思路呢？

考虑**随机化做法**！

考虑随机选择 $i ,j,k$ 中的随机一个，将它换成 $p$。下面证明这样是可行的：

证明：

我们设当前的三角形内剩余的顶点个数为 $c$（包括当前三点 $i,j,k$）。

则由 $p$ 分出的三个三角形中必有一个三角形内点数 $c_p \le \frac{c-1}{3}$ 

而我们取到这样的点的概率为 $\frac{1}{3}$，我们只需要取到这样的点$\lfloor\log_3n\rfloor+1$ 次，这至多为 $7$ 次。

于是失败概率 $q \approx \sum_{i=68}^{75} (C_{75}^i \times (\frac13)^{75-i}\times(\frac23)^i) \le 8.1·10^{-5}$ 极小概率会死，正确性保证。

给出代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

mt19937 myrand(time(nullptr));

void solve(){
    cout.flush();
    int n;
    cin >> n;
    int a = 1, b = 2, c = 3;
    while(1){
        cout << '?' << ' ' << a << ' ' << b << ' ' << c << '\n';
        cout.flush();
        int p = myrand() % 3;
        int x;
        cin >> x;
        if(x == 0) { cout << '!' << ' ' << a << ' ' << b << ' ' << c << '\n'; return; }
        if(p == 0) a = x;
        else if(p == 1) b = x;
        else c = x;
    }
}

int main(){
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
```

---

## 作者：ATION001 (赞：0)

话说这题严谨吗？

首先我们随机选择一个三角形的三个点 $x,y,z$。

得到中间的隐藏点 $a$。

将 $x,y,z$ 中的其中一个替换为 $a$。

如果还有隐藏点，重复上述过程。

为什么呢？

因为设 $x,y,z$ 中隐藏点数量为 $b$，根据[抽屉原理](https://baike.baidu.com/item/%E6%8A%BD%E5%B1%89%E5%8E%9F%E7%90%86/233776)，$x,y,z$ 与 $b$ 凑成的三个三角形中至少有一个不大于 $\frac{b-1}{3}$，每次我们会有 $\frac{1}{3}$ 的概率取到这样的点，因此几乎不会 TLE（当然，太倒霉了也有可能 TLE）。

通过这样的方式我们将时间复杂度维持在了 $O(\log n)$ 左右。
### 实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n;
signed main(){
	mt19937 myrand(time(nullptr));
	for(cin>>t;t;t--){
		cin>>n;
		int x=myrand()%n+1,y=myrand()%n+1,z=myrand()%n+1,a;
		while(x==y){
			y=myrand()%n+1;
		}
		while(z==x||z==y){
			z=myrand()%n+1;
		}
		while(true){
			cout<<"? "<<x<<' '<<y<<' '<<z<<endl;
			cin>>a;
			if(!a){
				cout<<"! "<<x<<' '<<y<<' '<<z<<endl;
				break;
			}else{
				int tmp=myrand()%3;
				if(!tmp){
					x=a;
				}else if(tmp==1){
					y=a;
				}else{
					z=a;
				}
			}
		}
	}
	return 0;
}
```

---

## 作者：Coffee_zzz (赞：0)

一共有 $1500$ 个点，但最多只能得到 $75 \times 4$ 个点的信息，且保证点的坐标不变，容易想到随机化。

我们考虑，初始时随机三个点 $a,b,c$，每次对 $a,b,c$ 进行询问，若返回的 $p$ 不为 $0$，则随机将 $a,b,c$ 中的一个数替换为 $p$。这样做可以使每次得到的三角形都在缩小，最终得到答案。

我们来证明一下这样做为什么是对的：由于 $a,b,c$ 中一定存在一个点，满足将该点修改为 $p$ 后三角形内包含的点的数量会变成原来的 $\dfrac 1 3$；取到这样的点的概率为 $\dfrac 1 3$，而我们只需要取到 $\log_3 n$ 次即可，期望的操作次数为 $3 \times \log_3 n  \approx 21$，远小于 $75$，满足题目要求。

---

## 作者：AK_400 (赞：0)

发现这题不让交 hack，于是猜测是随机化。

我们随便选三个点，每次询问之后将随机一个点替换成给定的点。

这样会有三个可能的三角形，由抽屉原理，其中一个三角形内部至多含有原三角形内三分之一的点，选中这个三角形的概率是 $\frac 1 3$。于是期望选中 $25$ 次，远高于 $\log_3n\approx 7$。所以这个做法可以通过。

code：


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
template<typename T>
void read(T &x){x=0;char c=getchar();bool neg=0;while(!isdigit(c)){if(c=='-')neg=1;c=getchar();}while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();if(neg)x=-x;}
#define read2(a,b) read(a),read(b)
#define read3(a,b,c) read(a),read(b),read(c)
#define read4(a,b,c,d) read(a),read(b),read(c),read(d)
#define read5(a,b,c,d,e) read(a),read(b),read(c),read(d),read(e)
#define read6(a,b,c,d,e,f) read(a),read(b),read(c),read(d),read(e),read(f)
#define fls fflush(stdout)
int n,i,j,k,p;
void slv(){
    read(n);
    mt19937_64 rng(time(0)^clock());
    i=rng()%n+1,j=rng()%n+1,k=rng()%n+1;
    while(j==i)j=rng()%k+1;
    while(k==i||k==j)k=rng()%n+1;
    while(1){
        cout<<"? "<<i<<" "<<j<<" "<<k<<endl;
        fls;
        read(p);
        if(p==0){
            cout<<"! "<<i<<" "<<j<<" "<<k<<endl;
            fls;
            return;
        }
        int r=rng()%3;
        if(r==0)i=p;
        else if(r==1)j=p;
        else k=p;
    }
}
signed main(){
    int T;read(T);while(T--)
    slv();
    return 0;
}
```

---

## 作者：wcy110614 (赞：0)

超级好玩的交互。先考虑怎么找到一组解：

最开始查询任何三个点 $a,b,c$，设这三个点覆盖三角形中的点点集为 $S$，于是交互器会返回一个点 $p\in S$，并且 $p\not \in\{a,b,c\}$，之后把 $a,b,c$ 中随机一个点切换成 $p$ 然后继续提问，不妨设这个随机点为 $a$。因为每一次三角形 $a,b,c$ 覆盖了 $p,b,c$，所以新的 $|S|$ 比旧的 $|S|$ 至少小 $1$ （因为减少了 $a$）。

这道题不能提交 hack，所以直接过了。

至于期望情况下的复杂度证明，难度远高于刚刚猜的结论。引用以下官方题解  [Codeforces Round 1009 (Div. 3) — Editorial - Codeforces](https://codeforces.com/blog/entry/140540) 。

代码就简单了。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e5+10;
int a,b,c,tt,n,ans;
inline void work(){
	cin>>n,a=1,b=2,c=3,ans=1;
	while(ans){
		cout<<"? "<<a<<" "<<b<<" "<<c<<endl,cin>>ans;
		if(!ans){fflush(stdout);break;}
		int rnd=rand();
		if(rnd%3==0)a=ans;
		if(rnd%3==1)b=ans;
		if(rnd%3==2)c=ans;
		fflush(stdout);
	}
	cout<<"! "<<a<<" "<<b<<" "<<c<<endl,fflush(stdout);
}
int main(){
	srand(time(0)),cin>>tt;
	while(tt--)work();
	return 0;
}
```

---

