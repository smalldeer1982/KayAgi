# Rudolf and Snowflakes (simple version)

## 题目描述

This is a simple version of the problem. The only difference is that in this version $ n \le 10^6 $ .

One winter morning, Rudolf was looking thoughtfully out the window, watching the falling snowflakes. He quickly noticed a certain symmetry in the configuration of the snowflakes. And like a true mathematician, Rudolf came up with a mathematical model of a snowflake.

He defined a snowflake as an undirected graph constructed according to the following rules:

- Initially, the graph has only one vertex.
- Then, more vertices are added to the graph. The initial vertex is connected by edges to $ k $ new vertices ( $ k > 1 $ ).
- Each vertex that is connected to only one other vertex is connected by edges to $ k $ more new vertices. This step should be done at least once.

The smallest possible snowflake for $ k = 4 $ is shown in the figure.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1846E1/2fc3f5caf761ddee75c017a3deae10ee696f63d1.png)After some mathematical research, Rudolf realized that such snowflakes may not have any number of vertices. Help Rudolf check if a snowflake with $ n $ vertices can exist.

## 样例 #1

### 输入

```
9
1
2
3
6
13
15
255
10101
1000000```

### 输出

```
NO
NO
NO
NO
YES
YES
YES
YES
NO```

# 题解

## 作者：xiazha (赞：4)

## 思路
~~我又来发暴力的题解了。~~

在下文中我将每个顶点连接 $k$ 个新顶点此操作称为延伸。


------------


首先，我们会发现，一个延伸了 $x$ 次的 $k$ 叉雪花的节点数实际上是 $k^0+k^1+k^2+\cdot \cdot \cdot+k^x$。接着，按题目描述，合格的雪花图必须至少延伸了两次，且至少要是 $2$ 叉雪花，也就是说 $x\ge 2$ 并且 $k\ge2$ 。最后，观察数据范围，$n\le10^6$，也就是说，这题我们可以用桶来标记当前这个节点数是否是一个合格的雪花的节点数，先预处理出来，注意如果预处理 $i$ 叉雪花图时当前的节点数时已经超过了 $10^6$，就要 ```break``` 掉，开始计算 $i+1$ 叉雪花，这样询问时就可直接用桶判断了。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int tt,t[1000001],n,sum,kk;
signed main()
{
	//预处理 
	for(int i=2;i<=1000;i++)//枚举 i叉 
	{
		sum=1;
		for(int j=1;j<=20;j++)//延伸次数 
		{
			kk=1;
			for(int k=1;k<=j;k++) kk*=i;
			sum+=kk;
			if(sum>=1000000) break;//超过范围break 
			if(j>=2) t[sum]=1;//延伸次数大于2时目前节点数标记可行 
		}
	}
	//询问 
	cin>>tt;
	while(tt--)
	{
		cin>>n;
		if(t[n]) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
```


---

## 作者：sgl654321 (赞：2)

### 题目大意
判断一个数 $n$ 是否可以写成 $1+k+k^2+k^3+\cdots+k^q$ 的形式。其中 $k\ge 2,q\ge 2$，$k,q$ 均为整数。$n\le 10^6$。
### 解题思路
观察到 $k$ 一定小于 $\sqrt{n}$，这里有 $k<10^3$。为什么？因为 $q\ge 2$。

直接打表就可以了。枚举 $k$，枚举 $q$，超过 $n\le 10^6$ 的范围了就跳出循环。这里我运用了等比数列求和公式：

$$n=\sum_{i=0}^{q}k^i=\dfrac{ k^{q+1}-1 }{k-1}$$

~~但其实没啥用~~。

### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long tt,n; 
bool f[1000010];
long long ksm(long long x,long long y){
	long long ret=1;
	for(int i=1;i<=y;i++)
		ret=ret*x;
	return ret;
}
int main(){
	cin>>tt;
	for(int k=2;k<=1010;k++)
		for(int q=2;;q++)
			if((ksm(k,q+1)-1)/(k-1)>1000000)break;
			else f[(ksm(k,q+1)-1)/(k-1)]=1;
	while(tt--){
		cin>>n;
		if(f[n])cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}

```

---

## 作者：Nwayy (赞：1)

考场上也是切完 E2 没剩多少时间了，前面的时间花的还是太多了。

---

观察一下就会发现，所谓“雪花图”，其实每一层的点数都是上一层的 $k$ 倍。

发现这个后题目可以转换成：给出一个整数 $n$，问是否能找出一个二元组 $(k,m)$ 使得 $\sum\limits_{i=0}^mk^i=n$，其中必须保证 $k \ge 1,m \ge 2$。

先考虑弱化版：对于 $10^6$ 级别的数据，我们显然可以枚举 $k \in [2,10^3]$，在此过程中让 $k^i$ 不断乘上 $k$，其实和题意是等价的，最后把这过程中得到的所有数在数组里标记即可。而注意到 $m \ge 2$，所以至少有 $k^2$，因此对于 $10^6$ 级别而言，枚举这么多就够了。时间复杂度 $\mathcal {O}(\sqrt n \log \sqrt n)$。

再来看 $10^{18}$ 级别的数据。我们显然不能按照 E1 做法去做，但是可以发现，对于某个整数 $n=k^0+k^1+k^2$，我们可以转换为 $k(k+1)=n-1$，这个显然可以直接判断是否合法，那我们 E1 中的预处理其实只是找 $m \ge 3$ 的情况而已。但是注意到，当 $k \ge 10^6$ 时，$m$ 不可能大于 $2$。所以我们只需要在原先的基础上多枚举到 $10^6$，把此过程中得到的所有数存进 ```map``` 里，剩下的只需判断是否有 $m=2$ 的情况即可。时间复杂度 $\mathcal {O}(\sqrt [3]{n} \log \sqrt [3]{n})$。

**提醒**：

1. 此做法最好特判 $1,2,3$。

1. E2 实现过程中容易爆， 最好先处理自乘的边界。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1000005
#define int unsigned long long
int n,m,i,j,ans,T,flag,x,P[N];
map<int,int>f;
int get(int a,int b){
	int cnt=0;
	while(a) a/=b,cnt++;
	return cnt;
}
void check(int k){
	int sum=0,s=1,p=P[k];
	for(int i=1;i<=p;i++){
		sum+=s,s*=k;
		if(i>=3 && sum<=(int)1000000000000000000) f[sum]=1;
	}
}
signed main(){
	for(i=2;i<=1000000;i++){
		P[i]=get(1000000000000000000,i);
		check(i);
	}
	scanf("%llu",&T);
	while(T--){
		scanf("%llu",&x);
		if((int)sqrt(x-1)*(int)(sqrt(x-1)+1)==x-1 && (int)sqrt(x-1)!=1 && (int)sqrt(x-1)!=0) printf("YES\n");
		else if(f[x]) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}

```


---

## 作者：Coffee_zzz (赞：1)

### 分析

发现 $n$ 很小，甚至可以打表过，那不犹豫直接打表。

我们首先观察给定的雪花：它的第 $1$ 层有 $1$ 个节点，第 $2$ 层有 $4$ 个节点，第 $3$ 层有 $16$ 个节点。

可以发现它第 $i\ (i \gt 1)$ 层的节点数为第 $i-1$ 层节点数的 $4$ 倍。

同理，对于 $k$ 为其他值的雪花，第 $i\ (i \gt 1)$ 层的节点数为第 $i-1$ 层节点数的 $k$ 倍，那么这个雪花的总点数就是 $1+k+k^2+k^3+\cdots k^{p-1}$，其中 $p$ 为这个雪花的层数。也就是说如果一个数可以写成 $1+k+k^2+k^3+\cdots k^{p-1}$ 的形式，它就可以作为一个雪花的顶点数。

由于题目要求 $k \ge 2$ 且 $p \ge 3$，那我们从 $2 \sim \sqrt {10^6}$ 枚举 $k$，从 $2 \sim \log 10^6$ 枚举 $p$，和超过了 $10^6$ 跳到下一层循环，把所有满足条件的数打上标记即可。

每一次询问直接看着标记 $O(1)$ 输出就行。

### 代码

```c++
const int P=1e6;
bool vis[P+5];
void init(){
	int las,p;
	for(int i=2;i<=1000;i++){
		las=i,p=i+1;
		while(1){
			las=las*i;
			p=p+las;
			if(p>P) break;
			vis[p]=1;
		}
	}
}
void solve(){
	int n;
	n=read();
	if(vis[n]) cout<<"Yes\n";
	else cout<<"No\n";
}
```

---

## 作者：Wf_yjqd (赞：0)

比完赛才知道 E2 多简单。。错失了打进前 $100$ 的机会。

------------

这题暴力打表啊，硬是费了我两次罚时。

考虑转换问题为 $n$ 是否能由 $\frac{k^x-1}{k-1}$（$x\ge3$）构成。

枚举好了，复杂度大约是 $\operatorname{O}(m\times\log{m})$ 吧（$m$ 为 $\sqrt{n}$ 的最大值）。

因为大于 $\sqrt{n}$ 就不会有答案。

------------

卡着倒数第二分钟交的。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
bool vis[ll(1e6+84)];
ll T,n;
int main(){
    ll cnt=0;
    for(ll i=2;i<=1e6;i++){
        cnt=1;
        for(ll j=1;(cnt-1)/(i-1)<=1e6;j++){
            cnt*=i;
            if(j>=3&&(cnt-1)/(i-1)<=1e6)
                vis[(cnt-1)/(i-1)]=1;
        }
    }
    scanf("%lld",&T);
    while(T--){
        scanf("%lld",&n);
        puts(vis[n]?"YES":"NO");
    }
    return 0;
}
```


---

## 作者：引领天下 (赞：0)

题意：

给定一个 $n$，试判断 $n$ 能否被表示为 $1+k+k^2+k^3+\dots+k^m$ 的形式。。

做法：

注意到题目的数据范围很小，那还有什么好说的，直接枚举 $k$，按题意模拟即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n;
signed main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        cin>>n;
        bool ok=0;
        for(int k=2;k<1000;k++){//枚举k
            int s=1+k+k*k,t=k*k;
            while(s<n)s+=t*=k;//计算
            ok|=s==n;
        }
        cout<<(ok?"YES":"NO")<<endl;
    }
    return 0;
}
```

---

