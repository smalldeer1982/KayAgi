# Ever-Hungry Krakozyabra

## 题目描述

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF833C/c33d858fd2851e05374522a30a7adabbf702fc1e.png)Recently, a wild Krakozyabra appeared at Jelly Castle. It is, truth to be said, always eager to have something for dinner.

Its favorite meal is natural numbers (typically served with honey sauce), or, to be more precise, the zeros in their corresponding decimal representations. As for other digits, Krakozyabra dislikes them; moreover, they often cause it indigestion! So, as a necessary precaution, Krakozyabra prefers to sort the digits of a number in non-descending order before proceeding to feast. Then, the leading zeros of the resulting number are eaten and the remaining part is discarded as an inedible tail.

For example, if Krakozyabra is to have the number $ 57040 $ for dinner, its inedible tail would be the number $ 457 $ .

Slastyona is not really fond of the idea of Krakozyabra living in her castle. Hovewer, her natural hospitality prevents her from leaving her guest without food. Slastyona has a range of natural numbers from $ L $ to $ R $ , which she is going to feed the guest with. Help her determine how many distinct inedible tails are going to be discarded by Krakozyabra by the end of the dinner.

## 说明/提示

In the first sample case, the inedible tails are the numbers from $ 1 $ to $ 9 $ . Note that $ 10 $ and $ 1 $ have the same inedible tail – the number $ 1 $ .

In the second sample case, each number has a unique inedible tail, except for the pair $ 45,54 $ . The answer to this sample case is going to be $ (57-40+1)-1=17 $ .

## 样例 #1

### 输入

```
1 10
```

### 输出

```
9
```

## 样例 #2

### 输入

```
40 57
```

### 输出

```
17
```

## 样例 #3

### 输入

```
157 165
```

### 输出

```
9
```

# 题解

## 作者：LinuF (赞：6)

~~这是一个很反套路的一道题目。~~

### 题目意思

对一个数进行操作把这个数字按照不降序进行排列，之后把所有的前导零去掉。

对 $[L,R]$ 里的数都进行操作，最后能得到多少不同的数。

### 思路

看见题目里面的区间 $[L,R]$，很容易就会想到去采用一般数位 $dp$ 套路中差分的方式。但仔细过后会发现不好统计前缀数量。所以要考虑采用别的思路解决问题。

仔细观察答案的数量，用搁板法考虑零到九分别分配多少位置数量发现答案的总数最多是 $C_{27}^{9}$。数量级在 $5\times10^6$ 以内。

有上面这样的性质那这题就有个另外的思路了，通过暴搜搜索出所有的分配情况，然后用 $check$ 的方式判断该方式组成的数字会不会在区间 $[L,R]$ 之内。

搜索的方式如下：
```cpp
void dfs(int u,int left){
    if(u==9){
        nums[u]=left;
        if(check(len,true,true)){
            ans++;
        }
        return;
    }
    for(int i=0;i<=left;i++){
        nums[u]=i;
        dfs(u+1,left-i);
    }
}
```
搜索出了答案我们可以考虑如何做到快速判断答案的是否正确。我采用数位 $dp$ 的思路，定义状态为 $f[pos][limit1][limit2]$ 分别表示从高位处理到低位的位置，是否贴着上界，是否贴着下界。我们能够发现一旦又不贴着上界还不贴着下界，说明此时是一定满足的，可以直接跳出。

具体实现是这样的:
```cpp
bool check(int pos,bool limit1,bool limit2){
    if(!pos){
        return true;
    }
    if((!limit1)&&(!limit2)) return true;
    int down=limit1 ? la[pos] : 0;
    int up=limit2 ? ra[pos] : 9;
    for(int i=down;i<=up;i++){
        if(!nums[i]) continue;
        nums[i]--;
        bool flag=false;
        if(check(pos-1,limit1&&(i==down),limit2&&(i==up))) flag=true;
        nums[i]++;
        if(flag) return true;
    }
    return false;
}
```
### 时间复杂度

计算时间复杂度，首先有搜索的时间 $5\times10^6$，在搜索的基础上面有 $check$ 的时间复杂度。我们可以发现只有贴着上界走或者贴着下界走才会搜到底，那搜索层数的最坏情况是位数 $18$,再乘遍历每个数的时间是 $10$，最坏的时间复杂度达到将近 $5\times10^8$。但这只是最坏情况，跑不满的。

---

## 作者：xzggzh1 (赞：1)

~~这就是 CF 评分 2700 的题吗，还真是有够好笑的呢~~

题意：

对一个数进行操作把这个数字按照不降序进行排列，之后把所有的前导零去掉。

对 $[L,R]$ 里的数都进行操作，最后能得到多少不同的数。

$1\leq L,R\leq 10^{18}$

---

模拟赛上遇到了，秒了，没发现是之前做过的题，这个题也没加入我的[刷题纪录](https://www.luogu.com.cn/blog/xzggzh/hao-ti-ji-lu)里，看到了还没有题解就来写一篇。

首先看到对 $[L,R]$ 里所有数计数可以直接想到数位 $\rm dp$ ，但是这个题最后的计数要重排过并且不能只是单纯的 $work(R)-work(L-1)$ 这样减去贡献，要计算的是去重后的数量。

再来思考一下操作过后会得到的数字，是一个单调不降没有前导零的数，这样的数在 $[1,10^{18}] $ 中有多少呢？

暴力 $dfs$ 一下就可以知道 ，大概在 $10^6$ 量级内，那么我们只要遍历所有的可行的答案然后判断一下是否可以重排得到一个在 $[l,r]$ ，这个是 $O(\log n)$ 的模拟一下就好了。

---

代码：（比赛时写的又臭又长）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
inline int R()
{
	char c;int res,sign=1;
	while((c=getchar())>'9'||c<'0')if(c=='-')sign=-1;res=c-'0';
	while((c=getchar())>='0'&&c<='9') res=res*10+c-'0';
	return res*sign;
}
const int a[]={1e0,1e1,1e2,1e3,1e4,1e5,1e6,1e7,1e8,1e9,1e10,1e11,1e12,1e13,1e14,1e15,1e16,1e17,1e18};
int num,l,r,mem[20],ll[20],rr[20],tmp[20],SSS;
bool ddd(int i,bool _l,bool _r)
{
	if(i==0) return 1;
	if(_l&&_r&&ll[i]==rr[i])
	{
		if(tmp[ll[i]]==0) return 0;
		tmp[ll[i]]--; 
		bool res=ddd(i-1,1,1);
		tmp[ll[i]]++;
		return res;
	}
	if(_l)
	{
		if(_r) 
		{
			for(int j=rr[i]-1;j>ll[i];j--)
			{
				if(tmp[j])
				{
					return 1;
				}
			}
			if(tmp[ll[i]])
			{
				tmp[ll[i]]--;
				bool res=ddd(i-1,1,0);
				tmp[ll[i]]++;
				if(res) return 1;
			}
			if(tmp[rr[i]])
			{
				tmp[rr[i]]--;
				bool res=ddd(i-1,0,1);
				tmp[rr[i]]++;
				if(res) return 1;
			}
		}
		else 
		{
			for(int j=ll[i]+1;j<=9;j++)
			{
				if(tmp[j])
				{
					return 1;
				}
			}
			if(tmp[ll[i]])
			{
				tmp[ll[i]]--;
				bool res=ddd(i-1,1,0);
				tmp[ll[i]]++;
				if(res) return 1;
			}
		}
	}
	else 
	{
		for(int j=rr[i]-1;j>=0;j--)
		{
			if(tmp[j])
			{
				return 1;
			}
		}
		if(tmp[rr[i]])
			{
				tmp[rr[i]]--;
				bool res=ddd(i-1,0,1);
				tmp[rr[i]]++;
				if(res) return 1;
			}
	}
	return 0;
}
inline void ck()
{
	if(mem[0]==18) return;
	for(int i=0;i<10;i++) tmp[i]=mem[i];
	if(ddd(18,1,1))++num;
	/*bool _l=1,_r=1;
	for(int i=18;i>=1;i--)
	{
		if(_l&&_r&&ll[i]==rr[i])
		{
			if(tmp[ll[i]]==0) return;
			tmp[ll[i]]--; 
		}
		else 
		{
			if(_l)
			{
				if(_r) 
				{
					for(int j=rr[i]-1;j>ll[i];j--)
					{
						if(tmp[j])
						{
							++num;return;
						}
						
					}
				}
				else for()
			}	
		}
	}*/
}
void dfs(int n,int st)
{
	ck();
	if(a[n-1]>SSS)return;
	if(n>18) return;
	for(int i=st;i<=9;i++)
	{
		mem[0]--;
		mem[i]++;
		dfs(n+1,i);
		mem[i]--;
		mem[0]++;
	}
}
signed main()
{
	freopen("greed.in","r",stdin);
	freopen("greed.out","w",stdout);
	l=R();r=R();
	if(r==1e18)
	{
		if(l>r/10)
		{
			++num;
		}
		r--;
	}
	mem[0]=18;SSS=r;
	for(int i=1;i<=20;i++)
	{
		ll[i]=l%10;
		rr[i]=r%10;
		l/=10;
		r/=10;
	}
	dfs(1,1);
	printf("%d\n",num);
//	return clock();
}
```



---

## 作者：zesqwq (赞：0)

这是一个复杂度优于标算的做法。

答案只有 $C_{27}^9$ 种，可以直接枚举。

$l, r$ 的限制太棘手了，我们考虑简化这个东西。

先把 $l$ 补全成和 $r$ 的位数一样，然后去掉他们的 $\text{lcp}$ 容易证明此时答案不变。

现在考虑如何 $\text{check}$。

假设 $l$ 的十进制表示是 $\overline {abcde}$, $r$ 的十进制表示为 $\overline{fghij}$，当前 $\text{check}$ 的数为 $\overline {klmno}$，（假设 $k\le l\le m \le n \le o$）。

我们发现如果 $k \in (a, f)$，那么 $\text{check}$ 已经结束了。

否则我们可以尝试匹配 $l$ 或 $r$。

以匹配 $r$ 为例，如果 $klmno$ 中有一个数是 $f$ 则可以匹配。

匹配过程如下：

我们先将那一位除去。

如果有一个数 $< f$ 则匹配已经成功了，如果所有数都 $> f$ 则匹配失败，否则直接匹配 $f$ 后继续匹配 $g$。

直接模拟就是 $O(ans \log^2 n)$，精细实现 $O(ans (k + \log n)), k = 10$。

这不是最优复杂度。

我们考虑一个性质：除去 $\text{lcp}$ 后的 $r$，如果 $g\le h, h \le i, i > j$ 的话（**注意到第一位有特殊性**），实际上该数的答案与 $r=\overline {fgh(i-1)9}$ 相同，原因也许显然，可以自己思考一下。

有了这个性质，我们可以把他强行搞成单调递增的。

不过用此方法显然可以将原序列搞成从第二位开始单调递增状物。

现在回头看那个匹配过程，$g$ 后继续匹配 $h$ 意味着 $[0, g)$ 中的所有数都被匹配了，且 $g$ 还有。

$[0, g)$ 中的所有数都被匹配了，且 $g$ 还有，这个比较过程类似于数的比较。

具体的，原数可以转换成一个十位的二十进制数，每一位代表该数码出现的次数。

这样可以做到 $O(k\times ans)$，其中 $k = 10$ 即进制数。

能使用二进制奇淫技巧优化至 $O(ans)$（当然精细实现也可以），但是经过测试，竟然变慢了。

这可能还不是最优做法，欢迎吊打我。

贴个代码，但写法比较古怪，可以用于对拍和证明正确性，不利于阅读：

```cpp
const int N = 30;
int len1, len2;
ll l, r, tab1[N], tab2[N];
void dfs(int u, int lst) {
    for (int i = lst; i <= 9; i++) dfs(u + 1, i);
}
int cntl[10], cntr[10], c[10];
#define For(i, j, k) for (i = (j); i <= (k); i++)
int lcp = 0;
#define int ll
inline bool check() {
    for (int i = tab2[lcp] + 1; i < tab1[lcp]; i++)
        if (c[i]) return 1;
    if (c[tab1[lcp]]) {
        bool flag = 0;
        --c[tab1[lcp]];
        for (int i = 0; i < 10; i++) {
            if (c[i] > cntr[i])
                return /*cout << "ftt:" << endl, */ ++c[tab1[lcp]], 1;
            if (cntr[i] > c[i]) {
                flag = 1;
                break;
            }
        }
        ++c[tab1[lcp]];
        if (!flag) return /*cout << "ftt:2" << endl, */ 1;
    }
    if (c[tab2[lcp]]) {
        // puts("CMKAKIOI");
        --c[tab2[lcp]];
        // cout << c[0] << ' ' << c[1] << ' ' << cntl[0] <<  ' ' << cntl[1] << endl;
        bool flag = 0;
        for (int i = 9; ~i; i--) {
            if (c[i] > cntl[i]) return ++c[tab2[lcp]], 1;
            if (cntl[i] > c[i]) {
                flag = 1;
                break;
            }
        }
        ++c[tab2[lcp]];
        if (!flag) return 1;
    }
    return 0;
}
signed main() {
    //     freopen("statement.in", "r", stdin);
    //     freopen("statement.out", "w", stdout);
    // int T;
    // read(T);
    // while (T--) {
    len1 = len2 = 0;
    memset(c, 0, sizeof(c));
    memset(cntl, 0, sizeof(cntl));
    lcp = 0;
    memset(cntr, 0, sizeof(cntr));
    memset(tab1, 0, sizeof(tab1)), memset(tab2, 0, sizeof(tab2));
    read(l, r);
    while (r) tab1[++len1] = r % 10, r /= 10;
    while (l) tab2[++len2] = l % 10, l /= 10;
    reverse(tab1 + 1, tab1 + len1 + 1);
    reverse(tab2 + 1, tab2 + len1 + 1);
    while (lcp < len1 && tab1[lcp + 1] == tab2[lcp + 1]) ++lcp;
    // for (int i = 1; i <= len1; i++) cout << tab2[i];
    // cout << endl;
    if (lcp == len1) {
        cout << 1 << endl;
        return 0;
    }
    ++lcp;
    if (lcp < len1) ++cntl[tab2[lcp + 1]], ++cntr[tab1[lcp + 1]];
    for (int i = lcp + 2; i <= len1; i++)
        if (tab1[i] >= tab1[i - 1])
            ++cntr[tab1[i]];
        else {
            int x = cntr[tab1[i - 1]];
            cntr[tab1[i - 1]] = 0, cntr[tab1[i - 1] - 1] += 1;
            // --cntr[tab1[i - 1]];
            // ++cntr[tab1[i - 1] - 1];
            break;
        }
    for (int i = lcp + 2; i <= len1; i++)
        if (tab2[i] <= tab2[i - 1])
            ++cntl[tab2[i]];
        else {
            int x = cntl[tab2[i - 1]];
            cntl[tab2[i - 1] + 1] += 1, cntl[tab2[i - 1]] = 0;
            break;
        }
    // c[0] = 3, c[1] = 7;
    // cout <<check() << endl;
    int ans = 0, clen = len1 - lcp + 1;
    memset(c, 0, sizeof(c));
    // cout << "lcp:" << lcp << endl;
    For(c[0], 0, clen) For(c[1], 0, clen - c[0])
        For(c[2], 0, clen - c[0] - c[1]) For(c[3], 0, clen - c[0] - c[1] - c[2])
            For(c[4], 0, clen - c[0] - c[1] - c[2] - c[3])
                For(c[5], 0, clen - c[0] - c[1] - c[2] - c[3] - c[4]) For(
                    c[6], 0, clen - c[0] - c[1] - c[2] - c[3] - c[4] - c[5])
                    For(c[7], 0,
                        clen - c[0] - c[1] - c[2] - c[3] - c[4] - c[5] - c[6])
                        For(c[8], 0,
                            clen - c[0] - c[1] - c[2] - c[3] - c[4] - c[5] -
                                c[6] - c[7]) {
        c[9] =
            clen - c[0] - c[1] - c[2] - c[3] - c[4] - c[5] - c[6] - c[7] - c[8];
        ans += check(); 
    }
    cout << ans << endl;
    // }
    return 0;
}
```

---

