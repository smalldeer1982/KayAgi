# [USACO23DEC] Farmer John Actually Farms B

## 题目描述

Farmer John 在他的农场上种植了 $N$（$1 \leq N \leq 2\cdot 10^5$） 株芦笋！然而，其中有一些植物存在基因差异，长得比其他植物快。第 $i$ 株植物的初始高度为 $h_i$ 英寸，之后每天，第 $i$ 株植物长高 $a_i$ 英寸。

FJ 更加钟爱其中的一些植物。他将给你一组由不同整数组成的数组 $t_1,\dots,t_N$，这个数组包含 $0$ 到 $N-1$ 的全部整数。他希望恰好有 $t_i$ 株植物比第 $i$ 株植物高。找到最少要经过多少天，才能满足 FJ 的要求，或者报告这个要求是不可能满足的。

## 说明/提示

### 样例解释 1

在第一组样例中，有 $6$ 组测试数据。

在第一组测试数据中，只有一株植物，所以要求在第 $0$ 天就已经满足。

在第二组测试数据中，需要让第一株植物比第二株植物矮。第   $1$ 天后，它们的高度为 $15,13$；第 $2$ 天后，它们的高度均为 $23$；第 $3$ 天后，它们的高度为 $31,33$，这是满足要求的第一天。

第三组和第四组测试数据与第二组类似。

在第五组测试数据中，两株植物的初始高度均为 $7$ 英寸，且每天均增长 $8$ 英寸，所以它们的高度永远相同。因此，条件永远无法满足。

在第六组测试数据中，初始高度不满足要求且增长速度均相同，所以条件永远无法满足。

### 样例解释 2

在第二组样例中，有 $2$ 组测试数据。

在第一组测试数据中，第 $4$ 天后的最终高度为 $19, 20, 21, 18, 16$。

在第二组测试数据中，第 $7$ 天后的最终高度为 $25, 17, 19, 35, 36$。

### 测试点性质

- 测试点 $3$ 满足 $N \le 2$。
- 测试点 $4-5$ 满足 $N \le 50$，$a_i, h_i \le 10^3$。
- 测试点 $6-8$ 满足 $N \le 10^3$。
- 测试点 $9-13$ 没有额外限制。

## 样例 #1

### 输入

```
6
1
10
1
0
2
7 3
8 10
1 0
2
3 6
10 8
0 1
2
7 3
8 9
1 0
2
7 7
8 8
0 1
2
7 3
8 8
1 0```

### 输出

```
0
3
2
5
-1
-1```

## 样例 #2

### 输入

```
2
5
7 4 1 10 12
3 4 5 2 1
2 1 0 3 4
5
4 10 12 7 1
3 1 1 4 5
2 4 3 1 0```

### 输出

```
4
7```

# 题解

## 作者：tder (赞：13)

伟大的不等式组。

---

令 $d_i(x)$ 表示第 $i$ 个植物经过 $t$ 天后的高度，有：

$$
d_i(x)=h_i+t\times a_i
$$

根据 $t$ 的定义，若用 $p_i$ 表示 FJ 希望长到第 $i$ 高的植物，易得，对于 $1\le x\le n$：

$$
p_{t_x+1}=x
$$

那么，若最少经过 $k$ 天后满足 FJ 的要求，显然有 $d_{p_1}(k)>d_{p_2}(k)>\cdots>d_{p_n}(k)$，即：

$$
\begin{cases}
d_{p_1}(k)>d_{p_2}(k) \\
d_{p_2}(k)>d_{p_3}(k) \\
\cdots \\
d_{p_{n-1}}(k)>d_{p_n}(k) \\
\end{cases}
$$

分开来说，对于排名相邻的两个植物 $x=p_i$ 和 $y=p_{i+1}$，有 $d_{x}(k)>d_{y}(k)$，即 $h_x+k\times a_x>h_y+k\times a_y$，化简得：

$$
(a_x-a_y)k>h_y-h_x
$$

分类讨论 $a_x-a_y$ 的正负：

- 当 $a_x-a_y>0$，即 $a_x>a_y$ 时，有 $k>\frac{h_y-h_x}{a_x-a_y}$；
- 当 $a_x-a_y<0$，即 $a_x<a_y$ 时，有 $k<\frac{h_y-h_x}{a_x-a_y}$；
- 当 $a_x-a_y=0$，即 $a_x=a_y$ 时，有 $0>h_y-h_x$，即 $h_x>h_y$：
  - 若 $h_x>h_y$，$k\in\mathbb{R}$；
  - 反之，若 $h_x\le h_y$，无解。
  
此时我们得到了 $n-1$ 个不等式。其中，有 $l_1$ 个不等式 $k$ 大于某值，$l_2$ 个不等式 $k$ 小于某值，$l_3$ 个结果 $k\in\mathbb{R}$，以及 $l_4$ 个无解。

若 $l_4>0$，显然无解，输出 $-1$。由于 $k\in\mathbb{R}$，可以忽略所有 $l_3$ 个结果。接下来考虑剩余的 $l_1$ 个 $k>q1_i$ 和 $l_2$ 个 $k<q2_i$。那么，根据初中课本中的「同大取大，同小取小」，易得 $k>\max(q1_i)$ 及 $k<\min(q2_i)$。合并，得：

$$
\max(q1_i)<k<\min(q2_i)
$$

- 若 $\max(q1_i)<\min(q2_i)$，且区间 $(\max(q1_i),\min(q2_i))$ 中至少含有 $1$ 个正整数，则 $k=\lfloor\max(q1_i)\rfloor+1$；
- 反之，则无解。

时间复杂度 $O(T\cdot n)$。

---

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5, M = 1e9 + 5;
int T, n, h[N], a[N], t[N], p[N];
double q1 = -1, q2 = N;
int work() {
    cin>>n;
    for(int i = 1; i <= n; i++) cin>>h[i];
    for(int i = 1; i <= n; i++) cin>>a[i];
    for(int i = 1; i <= n; i++) {
        cin>>t[i];
        p[t[i] + 1] = i;
    }
    if(n == 1) return 0;
    q1 = -1, q2 = M;
    for(int i = 1; i < n; i++) {
    	int x = p[i], y = p[i + 1];
		if(a[x] > a[y]) q1 = max(q1, 1.0 * (h[y] - h[x]) / (a[x] - a[y]));
		else if(a[x] < a[y]) q2 = min(q2, 1.0 * (h[y] - h[x]) / (a[x] - a[y]));
		else if(h[x] <= h[y]) return -1; 	
	}
    if(q1 < q2) {
		double r = floor(q1) + 1; 
		if(r < q2) return r;
		else return -1;
	} else return -1;
}
signed main() {
    cin>>T;
    while(T--) cout<<work()<<endl;
    return 0;
    // f(i) = h[x] + i * a[x], g(i) = h[y] + i * a[y]
	// f(i) > g(i)
	// h[x] + i * a[x] > h[y] + i * a[y]
	// (a[x] - a[y]) * i > (h[y] - h[x]) 
	// 1. a[x] - a[y] > 0, i > (h[y] - h[x]) / (a[x] - a[y])
	// 2. a[x] - a[y] < 0, i < (h[y] - h[x]) / (a[x] - a[y])
	// 3. a[x] - a[y] = 0, 0 > (h[y] - h[x])
	//   I.  h[y] - h[x] < 0, i in R
	//   II. h[y] - h[x] >= 0, i in empty
}
```

---

## 作者：Expert_Dream (赞：6)

[博客园](https://www.cnblogs.com/gsczl71/p/17909469.html)。

高级的说：解个不等式，低级的说：前缀和。

首先，我们先将所有 $a$ 变换位置到最终应该在的位置。

然后，我们可以通过 $a_i$ 和 $a_{i-1}$ 的高度差和速度差，算出来他们之间还需要多久可以符合要求，或者是多久就不符合要求了。拿出草稿纸，自己列举四种情况分别讨论。简单列举即可。具体的感觉不是特别好讲，还是直接看代码会更容易理解。

如果这个点开始合法，那么在这里进行标记，如果这里开始不合法，也搞一个标记。最后一遍前缀和，结束。

我被这道题卡了很久的问题是一些细节没有处理好。一些边界少加一，多加一的。随后在自己手搓 hack 下，终于过掉啦啊。

其实这一道题并不需要前缀和，但是个人认为前缀和可以更好地理解。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5+5;
int n,t[N];
struct node{
	int h,a;
}a[N],c[N];
bool cmp(pair<int,bool> a,pair<int,bool> b){
	if(a.first == b.first)
		return a.second > b.second;
	return a.first < b.first;
}
bool check(){
	for(int i = 2;i <= n;i++) if(a[i].h<=a[i-1].h) return false;
	return true;
}
vector<pair<int,bool> > v;
bool solve(){
	v.clear();
	//1为开始，0为结束。
	cin >> n;
	for(int i = 1;i <= n;i++) {
		cin >> a[i].h;
	}
	for(int i = 1;i <= n;i++) {
		cin >> a[i].a;
	}
	for(int i = 1;i <= n;i++) {
		cin >> t[i];
	}
	
	if(n==1){
		cout<<0<<endl;
		return true;
	}
	for(int i = 1;i <= n;i++){
		c[n-t[i]] = a[i];
	}
	for(int i = 1;i <= n;i++){
		a[i] = c[i];
	}
	if(check()){
		cout<<0<<endl;
		return true;
	}
	int res=0;
	for(int i = 2;i <= n;i++){
		if(a[i-1].h > a[i].h) {
			if(a[i].a <= a[i-1].a) {
				return false;
			}
			v.push_back({((a[i-1].h - a[i].h) / (a[i].a-a[i-1].a) + 1),1});
		}else if(a[i-1].h < a[i].h){
			if(a[i].a >= a[i-1].a) v.push_back({0,1});
			else {
				v.push_back({(a[i].h - a[i-1].h) % (a[i-1].a-a[i].a) == 0?(a[i].h - a[i-1].h) / (a[i-1].a-a[i].a):((a[i].h - a[i-1].h) / (a[i-1].a-a[i].a)+1),0});
				res++;
			}
		}else{
			if(a[i].a > a[i-1].a) v.push_back({0,1});
			else return false;
		}
	}
	sort(v.begin(),v.end(),cmp);
//	for(auto it:v){
//		cout<<it.first<<" "<<it.second<<endl;
//	}
	for(int it=0;it < v.size();it++){
		if(v[it].second == 1)
			res++;
		else
			res--;
		
		if(res == n-1 && v[it+1].first != v[it].first) {
			cout<<v[it].first<<endl;
			return true;
		}
	}
	
	
	return false;
}

signed main(){
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while(T--){
		if(!solve()) cout<<-1<<endl;
	}
	return 0;
}

```

---

## 作者：Macw07 (赞：4)

本题不能保证解法最优，但提供了本人参赛时的解题思路。

该问题采用了模拟和数学中的常规不等式方法。首先，我们对 FJ 给定的植物数组进行排序，以使数组呈单调递增或递减的性质，以便后期处理。为了方便，我们按照 FJ 对植物的预期高度从低到高进行排序。排序完成后，可确保第 $i$ 盆花的高度必须小于第 $i+1$ 盆花的高度，同时第 $i+2$ 盆花的高度也必须大于第 $i+1$ 盆花。

我们根据每一盆花的信息列出两条直线方程 $y1$ 和 $y2$，其中 $X$ 表示天数。我们的目标是尽量使 $X$ 的值小。

1. $y1 = change_i\times X + height_i$
2. $y2 = change_{i+1}\times X + height_{i+1}$

为确保 $y2 \gt y1$，我们可以列出以下不等式：

$change_i\times X + height_i \lt change_{i+1}\times X + height_{i+1}$

对该不等式进行移项操作，使得所有未知数在同一边：

$change_i\times X - change_{i+1}\times X \lt height_{i+1} - height_i$

对不等式左半部分进行因式分解：

$X \times (change_i - change_{i+1}) \lt height_{i+1} - height_{i}$

如果 $change_i - change_{i+1}$ 为正数，则不需要改变不等式的方向：

$X \lt \frac{(height_{i+1} - height_{i})}{(change_i - change_{i+1})}$

1. 如果不等式右半部分为负数，则表明 $X$ 在任何情况下都无法满足条件，即第 $i+1$ 盆花永远无法超越第 $i$ 盆花，因此输出 $-1$。

2. 如果不等式右半部分为正数，则整个程序所接受的最大天数应为该不等式的解，即第 $i+1$ 盆花在 $X$ 天之后将会被超越。我们可以计算出 $X$ 的上限 `upperLimit`。

如果 $change_i - change_{i+1}$ 为负数，则不等式符号需要改变方向：

$X \gt \frac{(height_{i+1} - height_{i})}{(change_i - change_{i+1})}$

1. 如果不等式右半部分为负数，则在任何天数之后花的高度都不会被超越，说明永远都不会被超越。

2. 如果不等式右半部分为正数，则只有在天数大于解时，第 $i+1$ 盆花才能达到 FJ 的要求，即第 $i+1$ 盆花要超越第 $i$ 盆花至少需要经过 $X$ 天。我们可以计算出 $X$ 的下限 `lowerLimit`。

只有在 $lowerLimit \leq X \leq upperLimit$ 的情况下，才是合法的，才能确保每盆花的高度都符合 FJ 的心理预期。然而，也可能出现 $upperLimit \leq lowerLimit$ 的情况，因此在这种情况下也需要输出 $-1$。

根据上述不等式方程，我们可以模拟代码。以下是该问题的 C++ 代码：

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

// 需要开long long，int存不下。
#define int long long
const int MAXN = 2e5;
int t, n;

// node用于记录每一盆花的信息。
struct node{
    int height;  // 花的初始高度。
    int change;  // 花高度的变化率。
    int rank;  // FJ心中花的高度排名。
    // 对这些花按照FJ的排名从矮到高排序。
    bool friend operator < (node a, node b){
        return a.rank > b.rank;
    }
} arr[MAXN + 5];

signed main(){
    cin >> t;
    while(t--){
        // 变量初始化。
        int lowerLimit = 0;
        int upperLimit = 0x7f7f7f7f;

        cin >> n;
        for (int i=1; i<=n; i++) cin >> arr[i].height;
        for (int i=1; i<=n; i++) cin >> arr[i].change;
        for (int i=1; i<=n; i++) cin >> arr[i].rank;

        // 对每一盆花进行排序，按照FJ心中的要求排序。
        sort(arr+1, arr+1+n);

        for (int i=1; i<n; i++){
            // 两直线平行的情况：斜率相同。
            // 如果两盆花的增长率相同，就比较两盆花的高度。
            // 判断第i+1朵花是否永远都超越不了第i朵花。
            if (arr[i].change == arr[i+1].change){
                if (arr[i].height >= arr[i+1].height){
                    cout << -1 << endl;
                    goto end;
                }
                continue;
            } 

            // 斜率不同的情况：
            // 1. 如果第i+1朵花可以超过第i朵花的话需要多久？
            // 2. 如果第i+1朵花本身就超过了第i朵花，多久就会被反超？
            if (arr[i].change - arr[i+1].change < 0){
                // 第i+1朵花需要limit天才可以超越第i朵花。
                if (arr[i+1].height - arr[i].height < 0){
                    double limit = ((arr[i+1].height - arr[i].height)*1.0)/(arr[i].change - arr[i+1].change);
                    if ((int)floor(limit) == (int)ceil(limit)) limit = ceil(limit) + 1;
                    else limit = ceil(limit);
                    lowerLimit = max(lowerLimit, (int)limit);
                } else continue;  // 第i朵花永远不会超越第i+1朵花。
            } 

            else{
                if (arr[i+1].height - arr[i].height < 0){
                    // 第i+1朵花永远超不多第i朵花。
                    cout << -1 << endl;
                    goto end;
                } else{
                    // 第i+1朵花经过limit天后就会被第i朵花超越。
                    double limit = ((arr[i+1].height - arr[i].height)*1.0)/(arr[i].change - arr[i+1].change);
                    if ((int)floor(limit) == (int)ceil(limit)) limit = ceil(limit) - 1;
                    else limit = floor(limit);
                    upperLimit = min(upperLimit, (int)limit);
                }
            }

            // 不满足不等式的解。
            if (lowerLimit > upperLimit){
                cout << -1 << endl;
                goto end;
            }
        }

        cout << lowerLimit << endl;
        end: ;
    }
    return 0;
}
```


---

## 作者：听取MLE声一片 (赞：4)

因为不同整数构成，所以数组 $t$ 是一个排列，换句话说这些竹笋按照 $t$ 从大到小排列后高度为严格升序。

一个序列是严格升序当且仅当每两个相邻的元素，前面的元素都小于后面的元素。

对于这个序列，求出每两个相邻元素满足要求的时间区间，再对这若干个区间求交即可。

满足要求的时间区间解一元一次不等式即可，分类讨论一下。

区间求交就是右端点取最大值，左端点取最小值，若最后区间能为合法区间，则左端点即为最早合法天数，否则一定不合法。



---

## 作者：Zi_Gao (赞：3)

> 题意：
>
> 有 $n$ 株植物，初始高度为 $h_i$，并且每天长 $a_i$。现在给了一些限制，问存不存在一天使得满足每个限制，给出最小解，其中每个限制是要第 $i$ 株植物比其他 $t_i$ 株植物高。
>
> $n,m\leq 2\cdot 10^5$ 以及 $1\leq h_i,c_i\leq 10^9$ 并且 $t_i$ 互不相同。

发现这个限制就是再说按高度排序后第 $i$ 株植物排在第 $t_i$ 位，那么不妨先把这个按高度排序后的植物数组处理出来，现在就只需要考虑相邻两个植物的高度关系即可，设符合条件在第 $x$ 天，设 $i$ 和 $j$ 相邻，要求 $i$ 比 $j$ 高：

1. $h_i\geq h_j$ 要求 $h_i+a_ix\gt h_j+a_jx$ 也就是 $x\gt \frac{h_i-h_j}{a_j-a_i}$。
2. $h_i\leq h_j$ 同理可得 $x\lt \frac{h_j-h_i}{a_i-a_j}$。

还有一些边界情况细节见代码。那么可以得到 $x$ 的上界和下界，若有解就是下界小于等于上界，输出下界即可。

我的实现有点垃圾。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ONLINE_JUDGE
#define INPUT_DATA_TYPE int
#define OUTPUT_DATA_TYPE int
INPUT_DATA_TYPE read(){register INPUT_DATA_TYPE x=0;register char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_DATA_TYPE x){if(x<0)x=-x,putchar('-');if(x>9)print(x/10);putchar(x%10^48);return;}

int h[200010],a[200010],p[200010],t[200010];

long long abss(long long x){return x<0?-x:x;}

long long floor_(long long a,long long b);

long long ceil_(long long a,long long b){
    if(a>=0&&b>=0) return (a+b-1)/b;
    else if(a<0&&b<0) return ((-a)+(-b)-1)/(-b);
    else return -floor_(abss(a),abss(b));
}

long long floor_(long long a,long long b){
    if(a>=0&&b>=0) return a/b;
    else if(a<0&&b<0) return (-a)/(-b);
    else return -ceil_(abss(a),abss(b));
}

void solve(){
    register int i,l=0,r=0x3f3f3f3f3f3f3f3fll,j;
    int n=read();
    for(i=0;i<n;++i) h[i]=read();
    for(i=0;i<n;++i) a[i]=read();
    for(i=0;i<n;++i) p[t[i]=read()]=i;
    for(i=0;i<n;++i){
        if(t[i]==n-1) continue;
        j=p[t[i]+1];
        if(h[i]>h[j]){
            if(a[i]>=a[j]) continue;
            else{
                if((h[i]-h[j])%(a[j]-a[i])) r=std::min(r,floor_(h[i]-h[j],a[j]-a[i]));
                else r=std::min(r,floor_(h[i]-h[j],a[j]-a[i])-1);
            }
        }else if(h[i]<h[j]){
            if(a[i]<=a[j]){
                r=std::min(r,-1ll);
                continue;
            }else{
                if((h[j]-h[i])%(a[i]-a[j])) l=std::max(l,ceil_(h[i]-h[j],a[j]-a[i]));
                else l=std::max(l,ceil_(h[i]-h[j],a[j]-a[i])+1);
            }
        }else{
            if(a[i]>a[j]) l=std::max(l,1ll);
            else r=std::min(r,-1ll);
        }
    }
    if(l<=r) print(l);
    else print(-1);
    return putchar('\n'),void();
}

signed main(){
    #ifndef ONLINE_JUDGE
    freopen("name.in", "r", stdin);
    freopen("name.out", "w", stdout);
    #endif

    int T=read();
    while(T--) solve();

    #ifndef ONLINE_JUDGE
    fclose(stdin);
    fclose(stdout);
    #endif
    return 0;
}
```


---

## 作者：Loser_Syx (赞：0)

发现 $t_i$ 是 $0 \sim n-1$ 的排列，故不存在相等关系，直接对 $t_i$ 排序。  
然后考虑一直缩小 $time$ 的取值范围，具体可以对于每个 $t_i$，列出 $h_i + a_i \times time > h_{i+1} + a_{i+1} \times time$，先判不成立或是所有解都成立，然后直接解 $time <$ 或 $time >$，最后得出一个形如 $a \leq time \leq b$ 的形式，答案为 $a$。注意取值范围可能存在 $a > b$，这不成立。

```cpp
const int N = 2e5 + 10;
struct node {
	int h, a, t;
	bool operator < (const node &a) const {
		return t < a.t;
	}
} s[201010];
// h1 + a1 * n > h2 + a2 * n
// a1 * n - a2 * n > h2 - h1
// (a1 - a2) * n > h2 - h1

// --------------------------

// a <= x <= b -> x >= a && x <= b
void solve() {
	int n = read();
	for (int i = 1; i <= n; ++i) read(s[i].h);
	for (int i = 1; i <= n; ++i) read(s[i].a);
	for (int i = 1; i <= n; ++i) read(s[i].t);
	sort(s + 1, s + 1 + n);
	int ans[2] = {0, (int)9e18};
	auto calc = [&](int h1, int a1, int h2, int a2) -> void {
		int big = 1; // >
		int x = (a1 - a2), y = (h2 - h1);
		if (x < 0) big = 0;
		if (big == 1) {
			ans[0] = max(ans[0], y / x + 1); 
		} else {
			ans[1] = min(ans[1], (y % x) ? (y / x) : (y / x - 1));
		}
	};
	int flg = 1;
	for (int i = 2; i <= n; ++i) if (s[i].h >= s[i-1].h) flg = 0;
	if (flg) return write(0, '\n'), void();
	for (int i = 1; i < n; ++i) {
		if (s[i].h <= s[i+1].h && s[i].a <= s[i+1].a) return write(-1, '\n'), void();
		if (s[i].a != s[i+1].a)calc(s[i].h, s[i].a, s[i+1].h, s[i+1].a);
		if (ans[0] > ans[1]) return write(-1, '\n'), void();
	}
	//cout << ans[0] << ' ' << ans[1] << '\n';
	write(ans[0], '\n');
}
signed main() {
	int T = read();
	while (T--) solve();
	return 0;
}
```

---

