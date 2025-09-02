# Reading Books (easy version)

## 题目描述

Alice 和 Bob 一共有 $n$ 本书要读。第 $i$ 本书有三个属性：阅读时间 $t_i$，$a_i$（为 $1$ 表示 Alice 喜欢这本书，为 $0$ 表示 Alice 不喜欢），$b_i$（为 $1$ 表示 Bob 喜欢这本书，为 $0$ 表示 Bob 不喜欢）。

他们需要从这些书中选择若干本，满足

- 这些书中至少有 $k$ 本是 Alice 喜欢的，至少有 $k$ 本是 Bob 喜欢的。
- 阅读的总时间最小（总时间为选中的书的 $t_i$ 的总和）

## 样例 #1

### 输入

```
8 4
7 1 1
2 1 1
4 0 1
8 1 1
1 0 1
1 1 1
1 0 1
3 0 0```

### 输出

```
18```

## 样例 #2

### 输入

```
5 2
6 0 0
9 0 0
1 0 1
2 1 1
5 1 0```

### 输出

```
8```

## 样例 #3

### 输入

```
5 3
3 0 0
2 1 0
3 1 0
5 0 1
3 0 1```

### 输出

```
-1```

# 题解

## 作者：Dream__Sky (赞：4)

考虑贪心。

以下的“对答案的贡献”是指对本数的贡献，不是时间的贡献。

有四种情况：

- 两人都不喜欢，对答案的贡献为 $0$，没用。
- 两人都喜欢，对答案的贡献为 $2$，存到 $a$ 数组中。
- A 喜欢，B 不喜欢，对答案的贡献为 $1$，存到 $b$ 数组中。
- A 不喜欢，B 喜欢，对答案的贡献为 $1$，存到 $c$ 数组中。

因为需要时间最少，所以需要先排序一遍。

因为四种情况的贡献是不同的，不好处理，所以我们可以将第二种（$b$ 数组）与第三种（$c$ 数组）情况下的书各拿出一本进行合并，放入 $a$ 数组中，也使它们的贡献变为 $2$。之后，我们可以再次将 $a$ 数组排序一遍，取出最前面的 $k$ 组，需要的时间就是它们的和。

无解的情况为合并后所有的书都不够到k组，那么怎么选都是不可能满足要求的。

代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10; 
int n,k,cnt1,cnt2,cnt3,daan;
int a[N],b[N],c[N];
signed main()
{
	cin>>n>>k;
	for(int i=1,time,A,B;i<=n;i++)
	{
		cin>>time>>A>>B;
		if(!A&&!B) continue;//第一种情况
		else if(A&&B) a[++cnt1]=time;//第二种 
		else if(A&&!B) b[++cnt2]=time;//第三种 
		else if(!A&&B) c[++cnt3]=time;//第四种 
	}
	
	sort(b+1,b+1+cnt2),sort(c+1,c+1+cnt3);//排序
	 
	for(int i=1;i<=min(cnt2,cnt3);i++)
		a[++cnt1]=b[i]+c[i];//合并，使贡献相同 
		
	if(cnt1<k) return cout<<-1,0;//无解 
	
	sort(a+1,a+1+cnt1);
	for(int i=1;i<=k;i++) daan+=a[i];
	cout<<daan;
	return 0;
}


```


---

## 作者：45dino (赞：2)

这里提供另一种做法，思路一致，可能更好写一点（因为STL？）

设集合 $A$ 是 $Alice$ 喜欢，$Bob$ 不喜欢的书，集合 $B$ 是 $Alice$ 不喜欢，$Bob$ 喜欢的书，集合 $C$ 是两人都喜欢的书。

两人都不喜欢的书由于对答案没有贡献，可以不考虑。

现在要做一件神奇的事情：

将集合 $A$ 从小到大排序，集合 $B$ 从小到大排序，将集合 $A$ 和集合 $B$ 里的元素两两合并（第一个和第一个合并，第二个和第二个合并……），放入集合 $D$ 。

楼上大佬都是枚举集合 $C$ 里面取 $i$ 个，集合 $D$ 里面取$k-i$个，但其实只要将集合 $D$ 混入集合 $C$ 从小到大排序，取前 $k$ 个就是答案。

复杂度为 $O(nlogn)$ ，比其他人 $O(n)$ 的复杂度略高。~~但也没高多少~~但更好想更好写一点（强行找理由

喜闻乐见的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> a,b,c;
int n,k,ans;
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		int t,A,B;
		scanf("%d%d%d",&t,&A,&B);
		if(A&&B)
			c.push_back(t);
		if(A&&!B)
			a.push_back(t);
		if(!A&&B)
			b.push_back(t);
	}
	sort(a.begin(),a.end());
	sort(b.begin(),b.end());
	for(int i=0;i<min(a.size(),b.size());i++)
		c.push_back(a[i]+b[i]);
	sort(c.begin(),c.end());
	if(c.size()<k)
	{
		puts("-1");
		return 0;
	}
	for(int i=0;i<k;i++)
		ans+=c[i];
	cout<<ans;
	return 0;
}
```


---

## 作者：pocafup (赞：2)

~~拿到题第一眼就应该观察出是个贪~~

显然，两人的选择只会尽量往价格小的选，而选小的不会对价格大的贡献产生影响。

~~第一眼也得看出俩人都不喜欢就得丢了~~

一开始容易想到对两个人都喜欢的做前缀和，然后二分选择两人都喜欢的之后贪心去选只有一个人喜欢的。

但是，我们发现这个二分其实不存在单调性，所以二分思路是错的。

继续分析，这题由于两人均要选 k 个喜欢的，所以答案只有一种情况：

```
选 a 本两人都喜欢的，然后两人各自选择自己喜欢的 n-a 本书
这个 a 可以为0
```

那么我们选的书肯定要尽可能价格小。

又观察到，当某人选了一本自己喜欢的书，另一个人也一定会选一本自己喜欢的书。因此，我们可以用贪心的方法合并两人选书过程：将两个人单独喜欢的书分别排序，然后从小到大两两合并，然后当成他俩都喜欢的书，价格为这两本书的和。

然后对两个人均喜欢的书价格进行排序，答案为 $\sum\limits_{i=1}^n val[i]$，其中 $val[i]$ 为第 $i$ 本两人均喜欢的书。

如果合并后两人均喜欢的书仍然不足 $n$，那么答案为 `-1`

代码：

```
#include <iostream>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <unordered_map>
#include <queue>
using namespace std;
/*
type1 : 俩人都喜欢
type2 : b喜欢c不喜欢
type3 : c喜欢b不喜欢
*/
#define int long long
int n,k,a,b,c,t,type1[200005],type2[200005],type3[200005],cnt1,cnt2,cnt3,ans;
signed main(){
  cin >>k >> n;
  for (int i=1;i<=k;i++){
    cin >> a >> b >> c;
    if (b==0 && c==0) continue;//俩都不喜欢买它干嘛(
    if (b==0 && c==1) type3[++cnt3] = a;
    if (b==1 && c==0) type2[++cnt2] = a;
    if (b==1 && c==1) type1[++cnt1] = a;
  }
  sort(type3+1,type3+cnt3+1);
  sort(type2+1,type2+cnt2+1);//分别排序
  for (int i=1;i<=min(cnt3,cnt2);i++) type1[++cnt1] = type3[i]+type2[i];//合并
  sort(type1+1,type1+cnt1+1);//排个序
  if (cnt1<n) {cout << -1; return 0;}//不够输出0
  for (int i=1;i<=n;i++) ans += type1[i];//统计答案
  cout << ans;
}
```

---

## 作者：Novelist_ (赞：1)

本题可以使用贪心。

输入一共有四种情况：

- 两人都喜欢，加入 $a$ 数组。
- Alice 喜欢，加入 $b$ 数组。
- Bob 喜欢，加入 $c$ 数组。
- 两人都不喜欢，扔了。

因为一本两人都喜欢的书等于两本两人各自喜欢的书，所以把两本两人各自喜欢的书合并成一本就等同一本两人都喜欢的书。然后我们排序一下 $b$ 数组和 $c$ 数组，然后把 $b,c$ 的每一项都加入 $a$ 数组,最后判断是否达到 $k$ 本，如果达到就求和输出，否则无解。

代码懒得放，要学会自力更生。

---

## 作者：封禁用户 (赞：1)

这题其实也可以用优先队列来做。

我们存的时候同时存两个数，显示当前的读书时间，然后是当前的 $i$，方便等下来加减。

```cpp
priority_queue<int, vector<pair<int, int> >, greater<pair<int, int> > > q1, q2, q3;
```
优先队列的定义。

优先队列的作用：当我们把一个数存进去时，它会以 $O(\log{n})$ 的速度存进去。并自动从小到大排序。

此处我们可证：当他们两个人对一本书都感兴趣，并且此书的阅读时间相对较少，那么选这本书的情况肯定是最优的。

~~（前面判断的代码就不放了，相信你们自己会打。）~~

主要部分：
```cpp
//first存的是读书时间，second存的是i，即位置。
  while(!q1.empty() && kk <= k)
  {
      t[q1.top().second] = 1;
      ans += q1.top().first;
      kk ++;
      q1.pop();
  }
  kk = 0;
  while(!q2.empty())
  {
      if(t[q2.top().second]) kk ++;
      else q3.push(q2.top());
      q2.pop();
  }
  if(kk < k)
  {
      while(!q3.empty() && kk < k)
      {
          ans += q3.top().first;
          kk ++;
          q3.pop();
      }
  }
  cout << ans;
```

---

## 作者：The_jester_from_Lst (赞：1)

本题考虑贪心。

对于每一组输入，若 $a_i$，$b_i$ 都为 $1$，我们把 $t_i$ 加入数组 $all$ 中。否则如果 $a_i$ 为 $1$，我们把 $t_i$ 加入数组 $al$ 中，否则如果 $b_i$ 为 $1$，我们把 $t_i$ 加入数组 $bl$ 中，否则这组数据就没用了。

输入时，为了特判无解，我们统计 $a_i$，$b_i$ 为 $1$ 的数量，只要有一个小于 $k$，则无解。输出 $-1$。

随后，我们对 $all$，$al$，$bl$ 三个数组进行排序。用 $i$，$j$，$k$ 三个指针分别指向 $all$，$al$，$bl$ 三个数组当前枚举到的位置。每次循环我们比较 $all_i$ 与 $al_j$ 加 $bl_k$ 的和，哪个小就让总和 $sum$ 加哪个，并移动对应的指针。如果某一个指针已经到底了，而选的书数量还不到 $k$，我们对三个数组再次分别单独循环直到数量够了为止。输出 $sum$ 即可。

附上代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int rd(){
	int jya=0,ysc=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')ysc=-1;ch=getchar();}
	while(isdigit(ch)){jya=jya*10+(ch-'0');ch=getchar();}
	return jya*ysc;
}
inline void wr(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)wr(x/10);
	putchar(x%10+'0');
}
int n,k,sumall,suma,sumb,sum,al[200086],bl[200086],all[200086],numa,numb;
signed main(){
	n=rd();k=rd();
	for(int i=1,t,a,b;i<=n;++i){
		t=rd();a=rd();b=rd();
		if(a&&b)all[++sumall]=t;
		if(a&&!b)al[++suma]=t;
		if(!a&&b)bl[++sumb]=t;
		numa+=(a==1);
		numb+=(b==1);
	}
	if(numa<k||numb<k){
		putchar('-');
		putchar('1');
		return 0;
	}
	numa=numb=0;
	sort(all+1,all+1+sumall);
	sort(al+1,al+1+suma);
	sort(bl+1,bl+1+sumb);
	int i=1,j=1,c=1;
	while(i<=sumall&&j<=suma&&c<=sumb){
		if(all[i]<al[j]+bl[c]){
			sum+=all[i];
			++i;
			++numa;
			++numb;
		}
		else{
			sum+=(al[j]+bl[c]);
			++j;
			++c;
			++numa;
			++numb;
		}
		if(numa>=k&&numb>=k)break;
	}
	while(i<=sumall&&numa<k&&numb<k){
		sum+=all[i];
		++numa;
		++numb;
		++i;
	}
	while(j<=suma&&numa<k){
		sum+=al[j];
		++numa;
		++j;
	}
	while(c<=sumb&&numb<k){
		sum+=bl[c];
		++numb;
		++c;
	}
	wr(sum);
	return 0;
}
```


---

## 作者：Clouder (赞：1)

每本书都有权值，每本书可能被 A 喜欢，可能被 B 喜欢，要求选出的书中，A 与 B 都至少喜欢 $k$ 本，求最小权值和。    
可以给书分类：  

0. A 与 B 都不喜欢    
1. A 喜欢   
2. B 喜欢   
3. A 与 B 都喜欢   

不难发现，二人都不喜欢的书是完全无效的。   
给每类书排序，做一遍前缀和。   
设选 $i$ 本 A 与 B 都喜欢的书，就要选 $k - i$ 本 A 喜欢的书， $k - i$ 本 B 喜欢的书。    
枚举 $i$ 求最小答案。   
```cpp
#include <cstdio>
#include <algorithm>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 2e6 + 100;
int n,k;
int A[maxn],B[maxn],C[maxn],acnt,bcnt,ccnt;
long long SA[maxn],SB[maxn],SC[maxn];
int main()
{
    read(n),read(k);
    for(int i = 1;i<=n;++i)
    {
        int t,a,b;
        read(t),read(a),read(b);
        if(a && b) C[++ccnt] = t;
        else if(a) A[++acnt] = t;
        else if(b) B[++bcnt] = t;
    }
    std::sort(A + 1,A + 1 + acnt);
    std::sort(B + 1,B + 1 + bcnt);
    std::sort(C + 1,C + 1 + ccnt);
    for(int i = 1;i<=acnt;++i) SA[i] = SA[i-1] + A[i];
    for(int i = 1;i<=bcnt;++i) SB[i] = SB[i-1] + B[i];
    for(int i = 1;i<=ccnt;++i) SC[i] = SC[i-1] + C[i];
    long long ans = 1ll << 60;
    for (int i = std::max(0,k - std::min(acnt, bcnt)); i <= ccnt && i <= k; ++i) 
        ans = std::min(ans, SA[k - i] + SB[k - i] + SC[i]);
    if (ans == 1ll << 60) puts("-1");
    else printf("%lld",ans);
    return 0;
}
```


---

## 作者：qusia_MC (赞：0)

直接贪心。
## 输入部分
- 输入的这本书如果说两个人都不喜欢，那没用。

- 如果两人都喜欢，则统计到一个数组 $a$ 中。

- 如果 A 喜欢 B 不喜欢，则统计到一个数组 $b$ 中。

- 如果 A 不喜欢 B 喜欢，则统计到一个数组 $c$ 中。

## 处理部分
由于选一本两人都喜欢的书可以顶两本两人只有一人喜欢的书，所以把两本两人喜欢的书合并成一本，这样两人都喜欢了。

所以，我们要做的就是：

- 排序 $b,c$ 数组。

- 把 $b,c$ 数组的第 $i$ 项合并到 $a$ 数组的后面。也就是 $a_j=b_i+c_i$。

- 最后排序一下 $a$ 数组，找到所有两人都喜欢的书（有一些是我们合并的）最小的那 $k$ 本（也就是编号为 $1 \sim k$ 的）。

## 输出部分
把排序后的 $a$ 数组前 $k$ 项直接求个和输出就行了。

总时间复杂度：$O(n \log n)$。

代码就不写了，~~我懒~~看到这的人大概都会写了吧？大佬们？

---

## 作者：HUANGRUI11 (赞：0)

正解考虑贪心，方法为二。

先讲一下大致思路，输入一共有四种情况：

$AB$ 都喜欢，$A$ 喜欢 $B$ 不喜欢，$B$ 喜欢 $A$ 不喜欢，和 $AB$ 都不喜欢（没用）。

所以选择前三种情况（设为 $a,b,c$）进行贪心维护。

### 方法一  快排加贪心

用三个数组分别储存下来，快排后将 $b$ 与 $c$ 各每次拿出一个合并后，放入 $a$ 数组中，也使它们相当于都被 $AB$ 喜欢。之后，我们可以再次将 $a$ 数组排序一遍，取出最前面的 $k$ 组，需要的时间就是它们的和。
如果 $a$ 数组小于 $k$ 组，则说明无解，输出 $-1$。

### 方法二  优先队列加贪心

优先队列将数以 $O(\log n)$ 存入后，会进行自动从小到大排序，也就是说输入 $n$ 个数并排序时间比快排还少（快排时间复杂度 $O(n\log n)$）。

然后就跟方法一的思路一样，用优先队列存入三种情况后，从  $b$ 和 $c$ 队列中每次个出队一组合并，然后再存入 $a$ 队列中，最后出队 $k$ 组即可。判断无解与前面相同。

不给代码，自己想去。

---

## 作者：oneton429 (赞：0)

### 题目大意

每本书都有权值，每本书可能被$A$喜欢，可能被$B$喜欢，要求选出的书中，$A$与$B$都至少喜欢$k$本，求最小权值和。

### Sol.

##### 大体思路

首先注意到，$A$与$B$都不喜欢的肯定不会对答案作出贡献。

所以存的时候直接`continue`掉就行

这题其实就是一个模拟$+$贪心

判断出答案存在之后按权值尽量小贪心选择书即可

##### 答案不存在?

设$A$喜欢的书个数为$cnt1$，$B$喜欢的书个数为$cnt2$，二人都喜欢的书的个数为$cnt3$

那么一个人最多能选到$min\{cnt1,cnt2\}+cnt3$个

如果$min(cnt1, cnt2)+cnt3 < k$那么肯定不能选出，输出`-1`

##### 如何选择?

将所有$A$喜欢的书的权值存入$book1[]$，所有$B$喜欢的书的权值存入$book2[]$，所有二人都喜欢的书的权值存入$book3[]$

将三个数组从小到大排序

设$book1[]$和$book2[]$当前遍历到了$now1(1\leqslant now1\leqslant min(cnt1, cnt2)$，$book3[]$当前遍历到了$now3(1\leqslant now3\leqslant cnt3)$

如果$book1[now1]+book2[now1]<book3[now3]$那么分开选书

否则选二人都喜欢的书

将选择的权值加到$ans$中，每人选择书的个数$tot$加加

当$tot \geqslant k$的时候即可结束遍历

*部分思路见代码*

### Code

```cpp
#include<cstdio>
#include<algorithm>
using std::min;
using std::sort;

int n, k, cnt1, cnt2, cnt3, now1 = 1, now3 = 1, ans, tot;
int book1[200020], book2[200020], book3[200020];

int main(void) {
    scanf("%d%d", & n, & k);
    for (register int i = 1, t, a, b; i <= n; ++i) {
        scanf("%d%d%d", & t, & a, & b);
        if (a && b)
            book3[++cnt3] = t;
        else if (a && !b)
            book1[++cnt1] = t;
        else if (!a && b)
            book2[++cnt2] = t;
    }
    sort(book1 + 1, book1 + cnt1 + 1),
    sort(book2 + 1, book2 + cnt2 + 1),
    sort(book3 + 1, book3 + cnt3 + 1);
    if (min(cnt2, cnt1) + cnt3 < k) { //判断能否选择
        puts("-1");
        return 0;
    }
    while (true) {
        if (now3 <= cnt3) //如果还有二人同时喜欢的书能选择
            if (book1[now1] + book2[now1] < book3[now3] && now1 <= min(cnt2, cnt1)) //如果还能分开选择，并且分开选择更优
                ans += book1[now1] + book2[now1],
                ++now1, ++tot;
            else //否则选择二人同时喜欢的书
                ans += book3[now3],
                ++tot, ++now3;
        else //如果没有二人同时喜欢的书能选择，那么只能分开选择
             //因为已经判断有解了，不用担心now1越界
            ans += book1[now1] + book2[now1],
            ++now1, ++tot;
        if (tot >= k)
            break;
    }
    printf("%d\n", ans);
    return 0;
}
```


>部分思路来自百度

---

