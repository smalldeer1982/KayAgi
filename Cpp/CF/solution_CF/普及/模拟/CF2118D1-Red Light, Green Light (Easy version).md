# Red Light, Green Light (Easy version)

## 题目描述

**这是问题的简单版本。不同版本的区别在于对 $k$ 和单个测试点中的 $n,q$ 总和的限制不同。**

给你一个长度为 $10^{15}$ 的长条和一个常数 $k$。在长条上有 $n$ 个格子上有一个信号灯，第 $i$ 个信号灯在格子 $p_i$ 处，同时具有一个初相 $d_i<k$。第 $i$ 个信号灯将在时刻 $z\times k+d_i,z$ 为整数时亮红灯，其他时刻亮绿灯。

时刻 $0$ 时你在某个格子处，面向正方向。每个时刻你将执行如下操作：
- 如果你所在的格子上有一个红色的信号灯，转向；
- 向你所面向的方向走一格。

你要处理 $q$ 个询问，询问给出时刻 $0$ 时你在格子 $a_i$，问时刻 $10^{100}$ 你是否已经走出长条的范围。

## 说明/提示

对于第一组数据，从 $1,2,3$ 出发的情况如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2118D2/ce9b61d8441ec2687644e4fcb1ecf9c698d0d9de.png)

对于第二组数据，从 $2$ 出发的情况如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2118D2/b6fc75687c6b2b664c445b1824b01121fde0aaa1.png)

## 样例 #1

### 输入

```
4
2 2
1 4
1 0
3
1 2 3
9 4
1 2 3 4 5 6 7 8 9
3 2 1 0 1 3 3 1 1
5
2 5 6 7 8
4 2
1 2 3 4
0 0 0 0
4
1 2 3 4
3 4
1 2 3
3 1 1
3
1 2 3```

### 输出

```
YES
NO
YES
YES
YES
YES
NO
NO
YES
YES
NO
NO
YES
NO
YES```

# 题解

## 作者：sSkYy (赞：2)

## 题解

对于 D1，数据范围很小，我们直接模拟题意 `DFS` 判断每个 $p_i$ 是否合法。

具体的，我们需要一个具有唯一性的状态，以便判断是否合法。

我们定义 $(u,t,op)$ 表示此时在第 $u$ 个红绿灯，过了 $t$ 单位的时间，$op$ 表示方向， $op=1$ 代表向右；$op=0$ 代表向左。

由于所有红灯亮起的间隔都是 $k$，遇到红灯，当且仅当 $t=l \times k+d_i$，也即 $t \equiv d_i \pmod k$。所以我们可以将 $t$ 改为模 $k$ 意义下的时间。如此一来 `vis` 数组的空间复杂度就只有 $O(n^2)$ 了。

下面考虑 `DFS` 的出口：

- 考虑 `NO` 的情况，我们拿一个 `vis[u][t][op]` 当做标记数组，显然如果我们重复到达了同一个状态，那么我们就走不出去了。

- 考虑 `YES` 的情况，如果当前 $u=n \land op=1$ 或者 $u=1 \land op=0$，那么下一步就可以走出所有红绿灯了。（$\land$ 代表并且）

时间复杂度：枚举 $n$ 个点，由于每个状态只会被遍历一次，且状态空间的大小为 $O(n^2)$，所以总的时间复杂度为 $O(n^3)$，可以通过。

## 代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=505;
int n,k,q;
int p[N],d[N],a[N];
int flag;
bool vis[N][N][2];

void dfs(int u,int t,bool op){
    if(flag!=0) return;
    if(vis[u][t][op]){
        flag=-1;
        return;
    }
    if((u==n&&op)||(u==1&&!op)){
        flag=1;
        return;
    }
    vis[u][t][op]=true;
    int v,new_t;
    bool new_op;

    if(op){
        v=u+1;
        new_t=t+p[v]-p[u];
    }else{
        v=u-1;
        new_t=t+p[u]-p[v];
    }
    new_t%=k;
    if(new_t<0) new_t+=k;
    if(new_t==d[v]) new_op=!op; 
    else new_op=op;
    dfs(v,new_t,new_op);
    vis[u][t][op]=false;
}

void solve(){
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>p[i];
    for(int i=1;i<=n;i++) cin>>d[i];
    cin>>q;
    for(int i=1;i<=q;i++) cin>>a[i];

    for(int i=1;i<=q;i++){
        if(a[i]>p[n]){
            cout<<"YES\n";
            continue;
        }
        flag=0;
        int pos=-1;
        for(int j=1;j<=n;j++)
            if(p[j]>=a[i]){
                pos=j;
                break;
            }
        int t=(p[pos]-a[i])%k;
        if(t<0) t+=k;
        bool op=((t==d[pos])?false:true);
        dfs(pos,t,op);
        cout<<((flag==1)?"YES\n":"NO\n");
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin>>T;
    while(T--) solve();
    return 0;
}
```

---

## 作者：DHeasy (赞：1)

- 2025.6.18：将“向前”和“向后”改成“向左”和“向右”。

---

[D2](https://www.luogu.com.cn/article/2k5y1mdp)。

设当前时间为 $t$，显然所有模 $k$ 相同的 $t$ 是本质相同的。

于是就把序列拆成 $n\times k$ 个点，其中 $(i,j)$（$1\le i\le n,0\le j\lt k$）表示当 $t\bmod k=j$ 时走到 $i$ 这一位。

然后就考虑找到 $(i,j)$ 向左和向右走到的第一个红灯处。

举向左的例子，如果 $(i,j)$ 向左能走到 $(u,v)$，当且仅当 $j+i-u\bmod k=v$。向右走同理。

然后对于一次询问，暴力的走，如果走出去了就是 `YES`，如果走到环就是 `NO`。

[提交记录](https://codeforces.com/contest/2118/submission/324338505)。

---

## 作者：hoko (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF2118D1)

注意到数据很小只有 $500$，所以想到可以模拟加记忆化，每一次暴力的去找到下一个要到的红绿灯的编号，再判断是红灯还是绿灯，如果是绿灯那方向不变，编号根据方向判定是加一还是减一，若果是红灯那方向改变，编号同理，同时用数组记录一下这一次遇到红灯的状态，三个状态分别为：编号，方向和时间，如果在模拟过程中编号小于 $1$ 或编号大于 $n$ 那么说明可以走出去，若果两次走到同一个状态，那么就不可能走出去。

---------

### code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1010101;
ll n,k,T,x,q,p[N],d[N],vis[510][3][510];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>k;
        for(int i=1;i<=n;i++)cin>>p[i];
        for(int i=1;i<=n;i++)cin>>d[i];
        cin>>q;
        while(q--){
            cin>>x;
            memset(vis,0,sizeof(vis));
            ll cnt=0,flag=1,now=0;
            for(int i=1;i<=n;i++){
                if(p[i]>=x){
                    now=i;
                    break;
                }
            }
            if(now==0){
            	cout<<"YES\n";
            	continue;
			}
            while(1){
                if((cnt+abs(p[now]-x)-d[now])%k!=0){
                	cnt+=abs(p[now]-x);
                    x=p[now];
                    if(flag)now++;
                    else now--;
                    if(now>n||now<1){
                        cout<<"YES\n";
                        break;
                    }
                }else{
                    if(vis[now][flag][(cnt+abs(p[now]-x)-d[now])%k]){
                        cout<<"NO\n";
                        break;
                    }
                    vis[now][flag][(cnt+abs(p[now]-x)-d[now])%k]=1;
                    cnt+=abs(p[now]-x);
                    x=p[now];
                    if(flag)now--;
                    else now++;
                    if(now>n||now<1){
                        cout<<"YES\n";
                        break;
                    }
                    flag^=1;
                }
            }
        }
    }
	return 0;
}

```

---

