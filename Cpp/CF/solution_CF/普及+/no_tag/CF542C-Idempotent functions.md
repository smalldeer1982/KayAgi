# Idempotent functions

## 题目描述

Some time ago Leonid have known about idempotent functions. Idempotent function defined on a set $ {1,2,...,n} $ is such function ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF542C/bd89689373264189cd84dae0d69467be68ca323b.png), that for any ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF542C/9a41c8470dbaa5967772aedda0040717aaf30fea.png) the formula $ g(g(x))=g(x) $ holds.

Let's denote as $ f^{(k)}(x) $ the function $ f $ applied $ k $ times to the value $ x $ . More formally, $ f^{(1)}(x)=f(x) $ , $ f^{(k)}(x)=f(f^{(k-1)}(x)) $ for each $ k&gt;1 $ .

You are given some function ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF542C/7ed3c9bd96ebefaf9c2ae2aa09921c0d35366e17.png). Your task is to find minimum positive integer $ k $ such that function $ f^{(k)}(x) $ is idempotent.

## 说明/提示

In the first sample test function $ f(x)=f^{(1)}(x) $ is already idempotent since $ f(f(1))=f(1)=1 $ , $ f(f(2))=f(2)=2 $ , $ f(f(3))=f(3)=2 $ , $ f(f(4))=f(4)=4 $ .

In the second sample test:

- function $ f(x)=f^{(1)}(x) $ isn't idempotent because $ f(f(1))=3 $ but $ f(1)=2 $ ;
- function $ f(x)=f^{(2)}(x) $ is idempotent since for any $ x $ it is true that $ f^{(2)}(x)=3 $ , so it is also true that $ f^{(2)}(f^{(2)}(x))=3 $ .

In the third sample test:

- function $ f(x)=f^{(1)}(x) $ isn't idempotent because $ f(f(1))=3 $ but $ f(1)=2 $ ;
- function $ f(f(x))=f^{(2)}(x) $ isn't idempotent because $ f^{(2)}(f^{(2)}(1))=2 $ but $ f^{(2)}(1)=3 $ ;
- function $ f(f(f(x)))=f^{(3)}(x) $ is idempotent since it is identity function: $ f^{(3)}(x)=x $ for any ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF542C/11e22b0eed3b852ef44d62d2479b42e2534a18a6.png) meaning that the formula $ f^{(3)}(f^{(3)}(x))=f^{(3)}(x) $ also holds.

## 样例 #1

### 输入

```
4
1 2 2 4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
2 3 3
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3
2 3 1
```

### 输出

```
3
```

# 题解

## 作者：素质玩家孙1超 (赞：1)


首先[暴力](https://www.luogu.com.cn/paste/88h5ttge)代码很好写(可以帮助更好理解题意)

---

但是答案可以达到千万级别，所以任然会TLE

打完暴力再看看题目

然后手玩数据

我随手打了一个例子

```
9
5 6 7 4 2 5 1 3 8
```

用暴力搞出原序列操作20次的

```
5 6 7 4 2 5 1 3 8
2 5 1 4 6 2 5 7 3
6 2 5 4 5 6 2 1 7
5 6 2 4 2 5 6 5 1
2 5 6 4 6 2 5 2 5
6 2 5 4 5 6 2 6 2
6//表示第六次是合要求的（下同）
5 6 2 4 2 5 6 5 6
2 5 6 4 6 2 5 2 5
6 2 5 4 5 6 2 6 2
9
5 6 2 4 2 5 6 5 6
2 5 6 4 6 2 5 2 5
6 2 5 4 5 6 2 6 2
12
5 6 2 4 2 5 6 5 6
2 5 6 4 6 2 5 2 5
6 2 5 4 5 6 2 6 2
15
5 6 2 4 2 5 6 5 6
2 5 6 4 6 2 5 2 5
6 2 5 4 5 6 2 6 2
18
5 6 2 4 2 5 6 5 6
2 5 6 4 6 2 5 2 5
```

然后发现，虽然答案会很大，但是每个位置的循环都不会很长，并且最后整个序列会循环

并且互相独立

所以我们想到对于每个位置，求出他的循环节开始的位置和长度

然后全部长度的最小公倍数就是整个序列的循环节

当整个序列循环一次后，就能得到答案

+ 注意：若整个循环节还没有某个序列的最初循环位置大，那么要答案要加上循环节的大小直至大于等于某个序列的最初循环位置。（有点绕，可以详见代码）

核心代码：

```cpp
n=R();
for(int i=1;i<=n;i++) a[i]=R();
for(int i=1;i<=n;i++)
{
	memset(vis,0,sizeof vis);
	x=a[i];	
	num=1;
	vis[x]=num;
	x=a[x];
	while(!vis[x])
	{
		vis[x]=++num;
		x=a[x];
	}
	m=max(m,vis[x]);//m表示最大的初始循环位置
	num=num-vis[x]+1;
	ans=lcm(ans,(long long )num);//ans表示整个循环节的长度
}
int add=ans;
while(ans<m) ans+=add;//特判
printf("%lld",ans);

```

---

## 作者：Shunpower (赞：0)

NOIP 之前找点信心。

## 题意

给你一个定义域和值域均为 $[1,n]$ 的函数 $f$ 在 $f(i),\forall i\in[1,n]$ 的值。定义 $f^{(1)}(x)=f(x),f^{(k)}(x)=f(f^{(k-1)}(x))$，你需要找出最小的 $k$ 满足 $f^{(k)}(f^{(k)}(x))=f^{(k)}(x)$。

$1\leq n\leq 200$。

## 思路

这种嵌套，再加上值域也在 $[1,n]$ 范围内，容易想到连边 $x\to f(x)$，于是 $f^{(k)}(x)$ 就被表示为一条从 $x$ 开始的路径。显然由于每个点的出度为 $1$ 这样的路径只有一条。

那么转化条件，这意味着我们要找到一个最小的 $k$ 满足从每个点走 $2k$ 步到达的点和走 $k$ 步到达的点相同。由于 $n$ 个点，每个点出度为 $1$ 的图一定是内向基环树森林，这说明从任意一个点走 $k$ 步都走到了环上，并且环长一定是 $k$ 的因数。

直接考虑求出所有环的环长，那么 $k$ 至少是它们的 $\text{lcm}$。于是我们先把 $k$ 设置为所有环环长的 $\text{lcm}$。

但是这显然不够。由于是内向基环树森林，有可能某个点走了 $\text{lcm}$ 步之后还没有到达环上，这就寄掉了。于是我们找出那些没有走到环上的点，考虑需要为它加上几步。

很明显加上之后我们仍然要保证 $k$ 是所有环环长的公共倍数，于是对于一个所在基环树环长为 $x$ 的不能走到环上的点，我们为 $k$ 不断加上除了 $x$ 以外的数的 $\text{lcm}$ 直到它可以走到环上。这样做显然一定是在保证仍然合法的情况下最优的。

然后这题就做完了。代码写得有点抽象：

```cpp
int n;
int f[N];
int lnk[N];
int dis[N];
int len,gate;
ll lcm=1;
ll rlcm[N];
void dfs(int x){
    if(dis[lnk[x]]){
        gate=lnk[x];
        len=dis[x]-dis[lnk[x]]+1;
        return;
    }
    else{
        dis[lnk[x]]=dis[x]+1;
        dfs(lnk[x]);
    }
}
pii condi[N];
int main(){
#ifdef Griffin
    freopen("hack.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
    cin>>n;
    fr1(i,1,n){
        cin>>f[i];
        lnk[i]=f[i];
    }
    lcm=1;
    fr1(i,1,n){
        dfs(i);
        lcm=1ll*lcm*len/__gcd(lcm,(ll)len);
        condi[i]=mp(len,(dis[gate]+len-1)/len);
        fr1(j,1,n){
            dis[j]=0;
        }
        len=0;
    }
    fr1(i,1,n){
        rlcm[i]=1;
        fr1(j,1,n){
            if(i==j){
                continue;
            }
            rlcm[i]=1ll*rlcm[i]*condi[j].fi/__gcd(rlcm[i],(ll)condi[j].fi);
        }
    }
    fr1(i,1,n){
        while(lcm/condi[i].fi<condi[i].se){
            lcm+=rlcm[i];
        }
    }
    cout<<lcm<<'\n';
    ET;
}
```


---

## 作者：DE_aemmprty (赞：0)

### 1 题目大意

**1.1 题目翻译：**

给定一个值域为 $[1,n]$ 的函数 $f(x)$，让你求出最小的 $k$，其中 $k$ 满足 $f^{(2k)}(x) = f^{(k)}(x)$。

其实我觉得这题你谷翻译十分到位，建议没读懂题的还是去看你谷翻译罢。

**1.2 数据范围：**

对于 $100\%$ 的数据：

* $1 \leq n \leq 200$

**1.3 \*关于数据范围**

这个 $n$ 其实可以开到 $2 \times 10^5$ 的，但前提是你得加一个高精度。~~出题人好仁慈，拜谢出题人。~~

### 2 解法分析

发现出现了 $f^{k}(x)$ 这种东西，不难想到建图。

我们可以把 $x$ 向 $a_x$ 连一条有向边。不难发现，整个图被分成了多个连通块，每一个连通块都形似基环树。我们可以把每一个环的大小和一个点到环的最短距离算出来。

现在，我们分两种情况讨论。设答案为 $k$：

* 如果结点 $u$ 在环中，设这个环大小为 $s$，那么这个结点必须绕至少 $s$ 次才能出现相等。所以，$s \ | \ k$。

* 如果结点 $u$ 不在环上，设这个结点到环的最短距离为 $d$，那么这个结点只有走至少 $d$ 次才能到环。所以，$k \geq d$。

于是，答案就简单了。我们把所有环的大小取最小公倍数 $\operatorname{lcm}$，然后算出第二种结点 $d$ 的最大值 $p$。如果 $p \leq \operatorname{lcm}$，那么就成立；否则，还要用带余除法计算出最小的 $w$，满足 $w \cdot \operatorname{lcm} \geq p$。此时，$w \cdot \operatorname{lcm}$ 即为答案。

### 3 AC Code

代码丑的要死，将就着看吧。

```cpp
int dfs(int x) {
    if (vis[x])
        return dis[x];
    vis[x] = 1;
    dfn[x] = ++ timetmp;
    int num = dfs(a[x]);
    if (vis[a[x]] == 1)
        p = a[x], num = dfn[x] - dfn[p] + 1;
    else if (cycle[a[x]] == 1) dis[x] = 1;
    else dis[x] = num + 1;
    if (p > 0 && vis[p] == 1)
        cycle[x] = 1, dis[x] = num;
    vis[x] = 2;
    return dis[x];
}

void solve() {
    cin >> n;
    f (i, 1, n)
        scanf("%lld", &a[i]);
    int k = 1;
    f (i, 1, n)
        if (!vis[i]) {
            p = -1;
            dfs(i);
        }
    f (i, 1, n)
        if (cycle[i])
            k = k * dis[i] / __gcd(k, dis[i]);
    int x = 0;
    f (i, 1, n)
        if (!cycle[i]) 
            x = max(x, dis[i]);
    if (x > k)
        k = ((x - 1) / k + 1) * k;
    printf("%lld\n", k);
}
```

---

