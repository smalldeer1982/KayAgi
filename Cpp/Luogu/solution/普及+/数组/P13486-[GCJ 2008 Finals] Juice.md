# [GCJ 2008 Finals] Juice

## 题目描述

你正在举办一场派对。为此，你正在通过混合三种不同类型的果汁来制作饮品：苹果汁、香蕉汁和胡萝卜汁。我们将这三种果汁分别记作 $A$、$B$ 和 $C$。

你希望决定饮品中每种果汁所占的比例，使得能让尽可能多的参加派对的人喜欢这款饮品。

每个人对于饮品中每种果汁都有一个最小比例的要求。只有当饮品中每种果汁的比例都大于等于他所要求的最小比例时，他才会喜欢这款饮品。

请你计算，最多能让多少人喜欢你调制的饮品。

## 说明/提示

**提示**

在第一个样例中，对于每种果汁，都有一个人希望饮品完全由该果汁组成！显然你只能满足其中一个人的要求。

在第二个样例中，你可以满足三个人中的任意两个人的要求。

在第三个样例中，如果你将三种果汁等分混合，五个人都会喜欢这款饮品。

**数据范围**

- $1 \leq T \leq 12$

**小数据集（测试集 1 - 可见）**

- $1 \leq N \leq 10$

**大数据集（测试集 2 - 隐藏）**

- $1 \leq N \leq 5000$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
3
10000 0 0
0 10000 0
0 0 10000
3
5000 0 0
0 2000 0
0 0 4000
5
0 1250 0
3000 0 3000
1000 1000 1000
2000 1000 2000
1000 3000 2000```

### 输出

```
Case #1: 1
Case #2: 2
Case #3: 5```

# 题解

## 作者：WuMin4 (赞：0)

## 题意

给出 $n$ 个三元组 $(a_i,b_i,c_i)$，你需要构造一组三元组 $(x,y,z)$，使得 $x+y+z=10000$，且满足 $a_i\le x,b_i\le y,c_i\le z$ 的数量最多。求出这个数量。

## 思路

首先考虑满足第一维的限制，于是按照 $a_i$ 升序排序并枚举。若现在枚举到了第 $i$ 项，令 $x=a_i$，则对于所有 $1\le i'\le i$ 都有 $a_{i'}\le x$

对于第二维，考虑使用 `multiset` 维护。在枚举第一维的同时将 $b_i,c_i$ 作为一个 `pair` 加入 `multiset`，然后再遍历这个 `multiset` 枚举第二维。若现在枚举到了第 $j$ 项，令 $y=b_j$，则对于所有 $1\le j'<j$ 都有 $a_{j'}\le x,b_{j'}\le y$。

因为 $x+y+z=10000$，且现在确定了 $x,y$，所以可以直接计算出 $z$ 的值，于是可以统计枚举项中 $c_i\le z$ 的数量，可以使用树状数组维护。总时间复杂度 $O(n^2\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,ans;
struct node{
	int x,y,z;
}a[5005];
bool cmp(node x,node y){
	return x.x<y.x;
}
multiset<pair<int,int>> s;
int c[10005];
void add(int x){
	x++;
	while(x<=10001) c[x]++,x+=(x&-x);
}
int qu(int x){
	x++;
	if(x<=0) return 0;
	int res=0;
	while(x) res+=c[x],x-=(x&-x);
	return res;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>T;
	for(int I=1;I<=T;I++){
		ans=0;
		s.clear();
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i].x>>a[i].y>>a[i].z;
		sort(a+1,a+1+n,cmp);
		for(int i=1;i<=n;i++){
			s.insert({a[i].y,a[i].z});
			memset(c,0,sizeof(c));
			for(auto j=s.begin();j!=s.end();j++){
				add(j->second);
				ans=max(ans,qu(10000-a[i].x-j->first));
			}
		}
		cout<<"Case #"<<I<<": "<<ans<<endl;
	}
	return 0; 
}
```

---

## 作者：DevilsFlame (赞：0)

~~这题跟标签数学与本题好像没有什么关系。~~

最简单的暴力，枚举 $A,B,C$，在此之上我们发现只要枚举 $i$ 满足 $c_i \le 10^4 - A - B,A \ge a_i,B \ge b_i$ 即可。时间复杂度 $O(N^3)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 1e1,M = 1e4;
int T,n,g,ans;
struct Node{
    int a,b,c;
}a[N];
inline void read(int &x) {
    x = 0;
    char s = getchar();
    while(s < '0' || s > '9') s = getchar();
    while(s >= '0' && s <= '9') {
        x = x * 10 + s - 48;
        s = getchar();
    }
    return;
}
inline bool cmp(Node a,Node b) {
    if(a.a != b.a) return a.a < b.a;
    else if(a.b != b.b) return a.b < b.b;
    else return a.c < b.c;
}
signed main() {
    read(T);
    for(int t = 1;t <= T;t ++) {
        read(n);
        for(int i = 1;i <= n;i ++) {
            read(a[i].a),read(a[i].b),read(a[i].c);
        }
        ans = 0;
        for(int i = 1;i <= n;i ++)
            for(int j = 1;j <= n;j ++) {
                int A = max(a[i].a,a[j].a),B = max(a[i].b,a[j].b);
                int C = M - A - B;
                if(C < 0) continue;
                for(int l = 1;l <= n;l ++) if(A >= a[l].a && B >= a[l].b && C >= a[l].c) g ++;
                ans = max(ans,g);
                g = 0;
            }
        printf("Case #%d: %d\n",t,ans);
    }
    return 0;
}
```
优化。  
我们发现，可以先枚举 $A_i$，取出 $A_j \le A_i$ 的数，另开数组按 $B$ 升序排序，对于任意 $B_j$，前面的数都比 $B_j$ 小，所以对于 $C = 10000 - A - B$，$C$ 只会越来越小，所以可以建大根堆，弹出不符合当前 $C$ 的数，因为之后的 $C$ 也不会满足。

细细品尝一下，这是用堆：
```cpp
            priority_queue < int > q;
            int l = 1;
            for(int j = 1; j <= lv; j++) {
                while(l <= lv && v[l].b <= v[j].b) q.push(v[l ++].c);
                int C = M - A - v[j].b;
                if(C < 0) break;
                while(!q.empty() && q.top() > C) q.pop();
                ans = max(ans,(int)q.size());
            }
```
这是暴力：
```cpp
            for(int j = 1; j <= lv; j++) {
                int C = M - A - v[j].b;
                if(C < 0) break;
                int g = 0;
                for(int l = 1;l <= j;l ++) if(v[l].c <= C) g ++;
                ans = max(ans,g);
            }
```
用堆可以省掉很多重复的遍历。

本题不卡常，但要是用较快的读入方式。

最后完整代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10, M = 1e4;
struct Node {
    int a,b,c;
} a[N];
struct Node2 {
    int b,c;
} v[N];
inline void read(int &x) {
    x = 0;
    char s = getchar();
    while(s < '0' || s > '9') s = getchar();
    while(s >= '0' && s <= '9') {
        x = x * 10 + s - 48;
        s = getchar();
    }
    return;
}
inline bool cmp(Node a, Node b) {
    if(a.a != b.a) return a.a < b.a;
    else if(a.b != b.b) return a.b < b.b;
    else return a.c < b.c;
}
inline bool cmp2(Node2 a, Node2 b) {
    return a.b < b.b;
}
int T,n;
signed main() {
    read(T);
    for(int t = 1;t <= T;t ++) {
        read(n);
        for(int i = 1;i <= n;i ++) read(a[i].a),read(a[i].b),read(a[i].c);
        int ans = 0;
        sort(a + 1,a + 1 + n,cmp);
        for(int i = 1;i <= n;i ++) {
            int lv = 0,A = a[i].a;
            for(int j = 1;j <= n;j ++) if(a[j].a <= A) v[++ lv] = {a[j].b,a[j].c};
            sort(v + 1,v + 1 + lv,cmp2);
            priority_queue < int > q;
            int l = 1;
            for(int j = 1; j <= lv; j++) {
                while(l <= lv && v[l].b <= v[j].b) q.push(v[l ++].c);
                int C = M - A - v[j].b;
                if(C < 0) break;
                while(!q.empty() && q.top() > C) q.pop();
                ans = max(ans,(int)q.size());
            }
        }
        printf("Case #%d: %d\n",t,ans);
    }
    return 0;
}
```

---

## 作者：abcxyz123 (赞：0)

「这道题应该怎么做呢？」 小 A 喃喃着。

这是一个夏天的温暖的夜晚，月亮在晴朗的天空中悬挂着，洒下一缕缕清亮的月光，不时地会有一丝微风，轻轻地抚摸着窗外的树，树叶温柔地发出「沙沙」的声响，远处传来小鸟「啾啾」的鸣叫。

月光照耀着，透过窗户洒进小 A 的屋里，撒到透着清冷的白光的电脑屏幕上，而小 A 则坐在椅子上，手中的鼠标来回移动。

屏幕上显示着[这样的一道题](https://www.luogu.com.cn/problem/P13486)：

> 你正在举办一场派对，会有 $N$ 个人来参加。为此，你正在通过混合三种不同类型的果汁来制作饮品：苹果汁、香蕉汁和胡萝卜汁。我们将这三种果汁分别记作 $A$、$B$ 和 $C$。
>
> 你希望决定饮品中每种果汁所占的比例，使得能让尽可能多的参加派对的人喜欢这款饮品。
>
> 每个人对于饮品中每种果汁都有一个最小比例的要求，分别为 $A_i$，$B_i$，$C_i$，其中 $A_i,B_i,C_i \le 10000$，$A_i+B_i+C_i \le 10000$，表示以万分之一为单位的比例。只有当饮品中每种果汁的比例都大于等于他所要求的最小比例时，他才会喜欢这款饮品。
>
> 请你计算，最多能让多少人喜欢你调制的饮品。
>
> 有 $T$ 组数据。$N \le 5000$，$T \le 12$。

小 A 努力地思索着，却没有一点思路。

「我难道连一个绿题都不会做了？」

「听老师说，一道题不会了，可以先想想简化的情况。」

「那就先想想**两种果汁的情况**吧。」

小 A 拿出一张纸和一支笔。

「两种果汁，苹果汁和香蕉汁。。。话说苹果汁不难喝呢，香蕉汁是什么味呢？应该和香蕉差不多吧。。。。。。」

小 A 的思路漫无目的的飘摇着。

小 A 的妈妈轻轻地走过来，手里端着一杯水。

「快，喝水，你都好久没喝水了。」

「哦。」 小 A 回过神来，接过了水。

喝完后，小 A 继续思考。

「两种果汁 $A$ 和 $B$，要求是 $A_i$ 和 $B_i$，如果两种的比例是 $X$ 和 $10000 - X$，那么当且仅当 $A_i \le X$ 且 $B_i \le 10000 - X$ 时这个人会喜欢。」

小 A 在纸上写着画着，思考了一段时间。

突然，小 A 灵机一动：

「**如果把它放到平面上呢？**」

「那么要求对应点 $(A_i, B_i)$，两种的比例对应 $(X, 10000 - X)$，这个人喜欢当且仅当 $(A_i, B_i)$ 在 $(X, 10000 - X)$ 的左下角。」

「只需要求以 $(0, 0)$ 和 $(X, 10000 - X)$ 为对角线端点的矩形的内部有多少个 $(A_i, B_i)$ 就行了。」

「但是，复杂度太高了吧。。。」

小 A 又想了一会儿。

「**如果对每个 $(A_i, B_i)$ 计算它对哪些 $X$ 有贡献会怎样？**」

小 A 开始在纸上推~~柿子~~式子，笔尖在纸上游走，发出「沙沙」的声音。

「$(A_i, B_i)$ 对 $X$ 有贡献当且仅当 $A_i \le X$ 且 $B_i \le 10000 - X$，即 $A_i \le X \le 10000 - B_i$。」

「所以枚举 $(A_i, B_i)$，然后令 $[A_i, 10000 - B_i]$ 里的数 $+1$ 即可。」

「设 $num_{i}$ 为对 $i$ 的贡献，利用差分。」

「令 $num_{A_i}$ 加 $1$，$num_{10000 - B_i}$ 减 $1$，最后前缀和，求 $\max_{0 \le X \le 10000} num_{X}$ 即可。」

「复杂度是 $O(N + V)$。」

小 A 呼了一口气。 「两种果汁的情况终于想出来了。」

「然后再考虑三种果汁。」

「三种果汁，不会是三维坐标系吧。。。三种的比例对应 $(X, Y, 10000 - X - Y)$，是一个倾斜的平面呢，贡献就不好算了。。。」

小 A 陷入了迷茫~~困惑惊慌无助~~之中。

「但是 $10000$ 不大呢。。。」

「**是不是可以枚举 $A$ 呢？**」

「将要求按 $A$ 从小到大排序，枚举到 $A = A_i$ 时，只保留 $1$ 到 $i$，然后去掉 $A_i + B_j + C_j > 10000$ 的 $j$，就**只需要考虑两种果汁 $B$ 和 $C$ 了**，只不过总的比例变成了 $10000 - A_i$。」

「两种的已经考虑出来了，就直接按那种做法做就行了。」

「复杂度是 $O(TN(N + V))$。」

「但是 $TN(N + V) \le 12 \times 5000 \times (5000 + 10000) \approx 9 \times 10 ^ 8$ 呢。。。」

小 A 赶紧看时限。

「$3$ 秒呢。。。只能祈祷常数小了。。。」

小 A 迟疑地吧代码写完，颤抖着把它交上去。

「不要 TLE，不要 TLE。。。。。。」

:::info[代码]
```cpp lines=9,13,14,16
......
// nd是每个人的要求
sort(nd + 1, nd + n + 1); // 按 A 排序
int ans = 0;
for (int i = 1; i <= n; i++) {
    int A = nd[i].a;
    cnt = 0;
    for (int j = 1; j <= i; j++) {
        if (A + nd[j].b + nd[j].c <= 10000) res[++cnt] = nd[j];
    }
    memset(num, 0, sizeof(num));
    for (int j = 1; j <= cnt; j++) {
        num[res[j].b]++;
        num[10000 - A - res[j].c + 1]--;
    } // 差分
    for (int j = 1; j <= 10000; j++) num[j] += num[j - 1];
    for (int j = 0; j <= 10000; j++) {
        ans = max_(ans, num[j]);
    }
}
writeln(ans);
......
```
:::

小 A 惊奇~~惊喜开心高兴激动喜悦~~地发现[他 AC 了](https://www.luogu.com.cn/record/227497168)！

「终于又做完一道题了太好了！」

小 A 于是又开了下一道题，鼠标在屏幕上跳跃舞动，月光似乎更加的明亮，它与屏幕的光应和着，交织着，在地板上映出了小 A 的影子。。。。。。

---

