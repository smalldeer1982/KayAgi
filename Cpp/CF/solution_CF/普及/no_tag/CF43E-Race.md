# Race

## 题目描述

Today $ s $ kilometer long auto race takes place in Berland. The track is represented by a straight line as long as $ s $ kilometers. There are $ n $ cars taking part in the race, all of them start simultaneously at the very beginning of the track. For every car is known its behavior — the system of segments on each of which the speed of the car is constant. The $ j $ -th segment of the $ i $ -th car is pair $ (v_{i,j},t_{i,j}) $ , where $ v_{i,j} $ is the car's speed on the whole segment in kilometers per hour and $ t_{i,j} $ is for how many hours the car had been driving at that speed. The segments are given in the order in which they are "being driven on" by the cars.

Your task is to find out how many times during the race some car managed to have a lead over another car. A lead is considered a situation when one car appears in front of another car. It is known, that all the leads happen instantly, i. e. there are no such time segment of positive length, during which some two cars drive "together". At one moment of time on one and the same point several leads may appear. In this case all of them should be taken individually. Meetings of cars at the start and finish are not considered to be counted as leads.

## 样例 #1

### 输入

```
2 33
2 5 1 2 14
1 3 11
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 33
2 1 3 10 3
1 11 3
```

### 输出

```
0
```

## 样例 #3

### 输入

```
5 33
2 1 3 3 10
1 11 3
2 5 3 3 6
2 3 1 10 3
2 6 3 3 5
```

### 输出

```
2
```

# 题解

## 作者：Hovery (赞：10)

[题面](https://www.luogu.com.cn/problem/CF43E)
# Sol

首先可以想到一个暴力做法。

先从 $1$ 到 $s$ 枚举一遍算出到第 $i$ 个位置每辆车所需的时间，在枚举每辆车两两间是否满足 $time_{i,s - 1} < time_{j,s - 1}$ 和 $time_{i,s} \geqslant time_{j,s}$ 若成立，则超车次数加 $1$。

时间复杂度 $O(s \times n ^ 2)$，显然不够优。

不难发现，超车与两辆车当前行驶了多少距离无关，我们可以考虑枚举时间。

先预处理出每辆车在每个时间点行驶的总路程，并求出最慢的那辆车行驶完全程所用的时间 $N$ 。

接着从 $2$ 枚举到 $N$，注：每辆车刚开始行驶时不能算超车。

对于当前的时间点 $T$，两辆车 $i$ 和 $j$ 有两种情况（路程用 $f$ 表示）。

$1.f_{i,T} = f_{j,T}$，若 $i$ 要完成一次超车，则需要满足 $f_{i,T - 1} < f_{j,T - 1}$，$f_{i,T + 1} > f_{j,T + 1}$。

$2.f_{i,T} \neq  f_{j,T}$，若 $i$ 要完成一次超车，则需满足 $f_{i,T - 1} < f_{j,T - 1}$，$f_{i,T} > f_{j,T}$。

时间复杂度大致为 $O(k \times n ^ 3)$，对于此题来说，是可以过的。


# Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int n, awa, num, t, v, N, ans, f[201][40000];
int main()
{
	cin >> n >> awa;
	for (int i = 1;i <= n;i++)
	{
		cin >> num;
		int j = 0;
		while(num--)
		{
			cin >> v >> t;
			while (t--)
			{
				f[i][++j] = f[i][j - 1] + v;
			}
		}
		N = max(N,j);
	}
   //预处理
	for (int o = 2;o < N;o++)
	{
		for (int i = 1;i <= n;i++)
		if (f[i][o])
		for (int j = 1;j <= n;j++)
		if (i != j && f[j][o])
		{
			if (f[i][o] == f[j][o])
			{
				if (f[i][o-1] < f[j][o-1] && f[i][o+1] > f[j][o+1])
				ans++;
			}
			else{
				if (f[i][o-1] < f[j][o-1] && f[i][o] > f[j][o])
				ans++;
			}
		}//计算超车
	}
	cout << ans;
}
```

---

## 作者：XL4453 (赞：2)

### 解题思路：

复杂度比官方题解以及另一篇题解优一个 $n$（$O(n^3)$ 优化到 $O(n^2)$）。

首先枚举两辆车，然后单独对其计算贡献，这样的复杂度是 $O(n^2)$，然后再 $O(k) 计算贡献$。

具体地，设 $s_{i,t}$ 为第 $i$ 辆车在 $t$ 时刻距离出发点的路径长度，定义 $f_t=s_{i,t}-s_{j,t}$，由于题目保证了不存在一段时间位置都相等的情况（也就对应了函数不存在平行于 $x$ 轴的区间），超车，也就被定义为函数与 $x$ 轴在非 $0$ 位置的交点个数。

然后考虑如何求这个交点个数，发现对于一段单调区间而言，它与 $x$ 轴的交点一定只有一个，而且可以通过这个区间的左右端点关于 $x$ 轴的位置关系算出来。

那么就只需要求出这个函数的拐点就行了，显然拐点就是车速改变的点，用两个指针维护分别指到哪里就行了。

---

实现上，需要注意的是有在拐点恰好等于 $0$，而且由于两个车速度变化的时间可能是相等的，所以一共需要往前推四个答案（包括当前这一个）才能精确判断是否出现了超车。

这一部分的细节可以看代码。

---

注意读入的是持续的时间。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,s,v[105][105],t[105][105],k[105],now1,now2,s1,s2,ti,ans,pa,l1,l2,l3,l0;
int main(){
	scanf("%d%d",&n,&s);
	for(int i=1;i<=n;i++){
		scanf("%d",&k[i]);
		for(int j=1;j<=k[i];j++)
		scanf("%d%d",&v[i][j],&t[i][j]),t[i][j]+=t[i][j-1];
		t[i][k[i]+1]=2147483647;
	}
	for(int i=1;i<=n;i++)
	for(int j=i+1;j<=n;j++){
		s1=s2=0;ti=0;
		now1=now2=1;
		l0=l1=l2=l3=-1;
		while(now1<=k[i]&&now2<=k[j]){
			int rnow1=now1,rnow2=now2;
			
			if(t[i][now1]<t[j][now2])pa=t[i][now1]-ti,ti=t[i][now1],now1++;
			else pa=t[j][now2]-ti,ti=t[j][now2],now2++;
			
			l0=l1;l1=l2;l2=l3;
			if((s1+v[i][rnow1]*pa)<(s2+v[j][rnow2]*pa))  l3=1;
			if((s1+v[i][rnow1]*pa)==(s2+v[j][rnow2]*pa)) l3=2;
			if((s1+v[i][rnow1]*pa)>(s2+v[j][rnow2]*pa))  l3=3;
			s1+=v[i][rnow1]*pa;s2+=v[j][rnow2]*pa;
			
			if(l2==-1||l3==2)continue;
			if(l2==2){
				if(l1==2){
					if(l0==-1)continue;
					ans+=(l0!=l3);
				}
				else ans+=(l1!=l3);
			}
			else ans+=(l2!=l3);
		}
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：_Dreams_ (赞：0)

[CF43E题目传送门](https://www.luogu.com.cn/problem/CF43E)

~~本人的第二篇题解没通过，改了之后被别人占了很气，来写这篇题解~~

### 题意：
一场汽车赛，给出 $n$ 辆车，赛道长度 $s$，接下来 $n$ 行，第 $i$ 行代表第 $i$ 个车的信息，每行第一个整数为 $k$，表示后面有 $k$ 组数据，每组两个数字，$v_{i,j}$，$t_{i,j}$，表示第 $i$ 辆车将以 $v_{i,j}$ 的速度持续 $t_{i,j}$ 秒，问期间发生了多少次超车事件。
### 分析：
模拟。先将每辆车的每一秒所在的距离打出，然后每两辆车判断他们之间的相邻的时间改变点（意思是某一辆车改变了速度）是否有超车现象，判断的具体过程是看两辆车的前后顺序有没有颠倒，若这一点两辆车是持平状态（就是距离一样），则忽略这一时间点，若当前时间点不同，则比较之前的有改变过的时间点和当前时间点的两辆车的前后位置。

### AC CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e2 + 10;
int mp[110][1005 * 100]= {0}
int tx[110], xx[110][105 * 105] = {0};//mp[i][j] 表示的是第 i 辆车在第 j 秒的位置。

int main() {
    int n, s;
    scanf("%d%d", &n, &s);
    int t, vv, tt;
    for (int i = 1; i <= n; i++) {
        int k;
        t = 0;
        scanf("%d", &k);
        for (int j = 1; j <= k; j++) {
            scanf("%d%d", &vv, &tt);
            for (int l = 1; l <= tt; l++) {
                mp[i][t + l] = mp[i][t + l - 1] + vv;
            }
            t += tt;
            xx[i][++xx[i][0]] = t;
        }
    }
    int num = 0, ans = 0;
    for (int j = 1; j < n; j++) {
        for (int k = j + 1; k <= n; k++) {//j，k 为遍历任意的不重复两辆车。
            int t1 = 0;
            for (int i1 = 1, i2 = 1; i1 <= xx[j][0] && i2 <= xx[k][0];) {
                int t;//t 表示的就是两辆车发生改变的时间点。因为只要发生变化，一定是在改变的时间点处。其他时间都是延续这种变化。
                if (xx[j][i1] < xx[k][i2]) {
                    t = xx[j][i1];
                    i1++;
                } else {
                    t = xx[k][i2];
                    i2++;
                }
                if ((mp[j][t1] > mp[k][t1] && mp[j][t] < mp[k][t]) || (mp[j][t1] < mp[k][t1] && mp[j][t] > mp[k][t])) {//判断是否有超车情况。
                    ans++;
                }
                if (mp[j][t] != mp[k][t])//t1 存的是前一个改变的时间点。若前一个也相同，就表示从 0 开始这两辆车一直距离相等，自然没有发生超车现象。
                    t1 = t;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
```

感谢各位的观看（制作不易，感谢点赞的读者，感谢审核的管理员）！！！

---

