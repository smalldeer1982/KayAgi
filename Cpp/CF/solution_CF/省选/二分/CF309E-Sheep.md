# Sheep

## 题目描述

Information technologies are developing and are increasingly penetrating into all spheres of human activity. Incredible as it is, the most modern technology are used in farming!

A large farm has a meadow with grazing sheep. Overall there are $ n $ sheep and each of them contains a unique number from 1 to $ n $ — because the sheep need to be distinguished and you need to remember information about each one, and they are so much alike! The meadow consists of infinite number of regions numbered from 1 to infinity. It's known that sheep $ i $ likes regions from $ l_{i} $ to $ r_{i} $ .

There are two shepherds taking care of the sheep: First and Second. First wakes up early in the morning and leads the sheep graze on the lawn. Second comes in the evening and collects all the sheep.

One morning, First woke up a little later than usual, and had no time to lead the sheep graze on the lawn. So he tied together every two sheep if there is a region they both like. First thought that it would be better — Second would have less work in the evening, because sheep won't scatter too much, being tied to each other!

In the evening Second came on the lawn, gathered the sheep and tried to line them up in a row. But try as he might, the sheep wouldn't line up as Second want! Second had neither the strength nor the ability to untie the sheep so he left them as they are, but with one condition: he wanted to line up the sheep so that the maximum distance between two tied sheep was as small as possible. The distance between the sheep is the number of sheep in the ranks that are between these two.

Help Second find the right arrangement.

## 样例 #1

### 输入

```
3
1 3
5 7
2 4
```

### 输出

```
1 3 2```

## 样例 #2

### 输入

```
5
1 5
2 4
3 6
1 7
2 6
```

### 输出

```
2 1 3 5 4```

## 样例 #3

### 输入

```
4
1 3
4 6
5 7
2 3
```

### 输出

```
1 4 2 3```

# 题解

## 作者：_maze (赞：3)

于七月二十六号更新，添加对于选取 $r$ 最小这一贪心的证明，并修复格式。

-----------------------

# 题目大意

不知道题目翻译是个啥。。。但讨论区有大佬给出了精确的翻译。我改得符合题目背景一点放上来：

每一个羊有一个活动区间 $l_i,r_i$。

现在，你需要重新排列 $n$ 只羊，使活动区间相交的羊之间的最大距离最小，输出方案。

距离定义为两只羊中间的羊的数量（其实无所谓了，毕竟只要输出方案）。

# 做法

二分加贪心。

二分答案，问题变成了保证两个相交的羊之间距离不超过二分的答案 $mid$。

不妨从小到大选择这个位置应该放哪一只羊，那么我们可以维护出一个数 $fin$，表示每只羊当前最远能放到的位置是哪里。

首先判断无解情况。设当前选择到了序列的位置 $i$ ，我们统计出数组  $finc$，$finc_j$ 表示 $fin$ 数组值在从 $i$ 到 $j$ 的羊的个数。

显然，无解的情况就是 $finc_j > j-i$ 。证明：根据 $fin$ 的定义，每次选择后，限制变多，$fin$ 不会变大。如果大于，就不能将 $fin$ 在 $[i,j]$ 之间的羊塞进 $j-i+1$ 个位置中。

然后我们考虑这个位置放哪只羊。根据无解情况，我们发现了一个限制：如果 $finc[j]=j-i$，那么我们放的羊肯定要小于等于 $j$。不然放下一只羊时必定会导致无解情况（$finc$ 可能会增加，$j-i$ 必定会减小）。而我们只需要满足 $j$ 最小的限制就行了。原因是满足了以后之后的 $finc$ 都会减一，避免了上面的情况。

满足上面的限制后，我们后贪心地选取 $r$ 最小的羊。

考虑证明这个贪心：

考虑归纳证明。现在有两个点 $x$ 和 $y$ 且 $fin_x,fin_x$ 均小于最小的限制。那么决定到底选哪个点的就是会更改的 $fin$ 的多少。由于这个更改对 $fin$ 来说是单调不增的，所以我们希望更改的越少越好。

更改 $fin$ 的前提是这个区间与当前区间相交，也就是说，我们想要当前相交数尽可能小。

不妨设 $r_x < r_y$。那么对于 $r_i >= r_x$ 我们选取 $x$ 更优。因为此时相交判断条件为 $l_i < r$，而 $r_x < r_y$，因此更不容易相交。

对于 $r_i < r_x$，此时根据归纳假设，我们选取 $i$ 会比选取 $x$ 更优。矛盾，因此这种情况不会存在。因此我们证明了贪心的正确性。

最后一个步骤，选择完点后，我们要根据这个点更新之后羊的 $fin$。具体地，我们要保证与之相交的点最远放到的位置小于等于 $i+mid$。

也许我讲的不够清楚，我再把 check 的总过程放上来：

```cpp
inline bool check(int mid)
{
	for(int i = 1;i <= n;i ++) fin[i] = n, ans[i] = 0, fl[i] = 0;
	for(int i = 1;i <= n;i ++)
	{
		int b = 0, p = 0;
		memset(finc, 0, sizeof(finc));
		for(int j = 1;j <= n;j ++) if(!fl[j]) finc[fin[j]] ++;//统计 fin 为 j 的羊的只数
		for(int j = 1;j <= n;j ++) finc[j] += finc[j - 1];	//实际上 finc 就是求一遍前缀和
		for(int j = i;j <= n;j ++) if(finc[j] > j - i + 1) return 0;//判无解（被标记的点统计 finc 时就没有贡献，无需额外判断）
		for(int j = n;j >= i;j --) if(finc[j] == j - i + 1) b = j;//寻找最小的限制
		for(int j = 1;j <= n;j ++) if(!fl[j] && fin[j] <= b && r[j] < r[p]) p = j;//在限制内寻找最小的 r
		fl[ans[i] = p] = 1;//标记，之后不能再选
		for(int j = 1;j <= n;j ++) if(l[j] <= r[p] && l[p] <= r[j]) fin[j] = min(fin[j], i + mid);//更新fin
	}
	return 1;
}
```

为了方便判断，我在主函数中将 $r[0] = INF$。需要注意一下。



------------

# 后记

其实，我们判断无解时用了一个叫做霍尔定理的东西。但由于太过显然，我就直接证了一遍。有兴趣的同学可以自行了解。

---

## 作者：luo_shen (赞：0)

[题面](https://www.luogu.com.cn/problem/CF309E)

## 分析

求的是最大值最小，肯定容易想到二分，该题目的答案的单调性是存在的，因为如果你找到一组合法的解，可以将距离最大的两个区间的距离再增大，这样更大的答案一定是能得到的。

既然我们已经得到了二分的合理性，那么我们需要考虑的只有如何检验一个答案的合理性。如果我们往序列中加入一个新区间，此时会影响与其相交的区间可以放置的位置范围，但是这样很难找到一个区间应该放在它对应的位置范围中的哪一个位置。既然如此，我们不如直接将每次加入的区间放在序列末尾，这样就省去了寻找一个区间可以放置在序列中的位置的范围，只需要知道区间可以放置的位置的最大值即可。  
我们再考虑统计一个 $cnt_{i,j}$ 表示在加入第 $i$ 个区间时，必须要放置在 $[i,j]$ 的区间有多少个，显然 $cnt_{i,j}\le j-i+1$，不然区间数大于位置个数，无解。有解的情况，找到第一个 $cnt_{i,j}=j-i+1$ 的位置，这 $j-i+1$ 个区间会刚好将位置 $[i,j]$ 放满。  
在这 $j-i+1$ 个区间中，显然影响其它区间数量最少的区间放在最前面是最优的。假定我们选择区间 $x$ 作为我们放在 $i$ 位置的的区间，存在一个区间 $y$ 满足必须放在位置范围 $[i,j]$ 内且 $r_y>r_x$，如果此时有一个另外的区间 $z$，满足 $r_z>l_x,r_z>l_y$，那么显然 $x$ 和 $z$ 相较于 $y$ 和 $z$ 来说更不容易相交。如果区间 $z$ 仅和区间 $x$ 相交不和区间 $y$ 相交，那么 $z$ 一定在 $x$ 之前被放置。因此我们在选择放在 $i$ 位置的区间可以直接选择必序放在位置范围 $[i,j]$ 内的区间中 $r$ 最小的。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace IO{
    template<typename T>
    inline void read(T &x){
        x=0;
        int f=1;
        char ch=getchar();
        while(ch>'9'||ch<'0'){
            if(ch=='-'){
                f=-1;
            }
            ch=getchar();
        }
        while(ch>='0'&&ch<='9'){
            x=x*10+(ch-'0');
            ch=getchar();
        }
        x=f==1?x:-x;
    }
    template<typename T>
    inline void write(T x){
        if(x<0){
            putchar('-');
            x=-x;
        }
        if(x>=10){
            write(x/10);
        }
        putchar(x%10+'0');
    }
    template<typename T>
    inline void write_endl(T x){
        write(x);
        putchar('\n');
    }
    template<typename T>
    inline void write_space(T x){
        write(x);
        putchar(' ');
    }
}
using namespace IO;
const int N=2010;
int n,l[N],r[N],ans_pos[N],pos_max[N],flag[N],cnt[N],Ans[N];
bool check(int dis){
    for(int i=1;i<=n;i++){
        flag[i]=0;//flag表示区间i的位置是否已经选定
        pos_max[i]=n;//pos_max表示区间i在排列中位置的最大值
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cnt[j]=0;
        }
        for(int j=1;j<=n;j++){
            if(!flag[j]){
                cnt[pos_max[j]]++;
            }
        }
        for(int j=1;j<=n;j++){
            cnt[j]+=cnt[j-1];
        }//前缀和统计cnt
        for(int j=i;j<=n;j++){
            if(cnt[j]>j-i+1){//不合条件的情况
                return 0;
            }
        }
        int mx=0;
        for(int j=i;j<=n;j++){
            if(cnt[j]==(j-i+1)){
                mx=j;
                break;
            }
        }
        int pos=n+1;
        for(int j=1;j<=n;j++){
            if(!flag[j]&&pos_max[j]<=mx&&r[j]<r[pos]){
                pos=j;
            }//寻找最优区间
        }
        flag[pos]=1;
        ans_pos[i]=pos;//标记若最大值为dis,排列中第i位的区间为哪个
        for(int j=1;j<=n;j++){
            if(l[j]<=r[pos]&&l[pos]<=r[j]){
                pos_max[j]=min(pos_max[j],i+dis);
            }//更新限制
        }
    }
    return 1;
}
signed main(){
    read(n);
    r[n+1]=INT_MAX;
    for(int i=1;i<=n;i++){
        read(l[i]),read(r[i]);
    }
    int left=1,right=n-1;
    while(left<=right){
        int mid=(left+right)>>1;
        if(check(mid)){
            right=mid-1;
            memcpy(Ans,ans_pos,sizeof(ans_pos));//找到答案并更新
        }
        else{
            left=mid+1;
        }
    }
    for(int i=1;i<=n;i++){
        write_space(Ans[i]);
    }
    return 0;
}

```


---

