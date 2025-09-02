# Motarack's Birthday

## 题目描述

Dark is going to attend Motarack's birthday. Dark decided that the gift he is going to give to Motarack is an array $ a $ of $ n $ non-negative integers.

Dark created that array $ 1000 $ years ago, so some elements in that array disappeared. Dark knows that Motarack hates to see an array that has two adjacent elements with a high absolute difference between them. He doesn't have much time so he wants to choose an integer $ k $ ( $ 0 \leq k \leq 10^{9} $ ) and replaces all missing elements in the array $ a $ with $ k $ .

Let $ m $ be the maximum absolute difference between all adjacent elements (i.e. the maximum value of $ |a_i - a_{i+1}| $ for all $ 1 \leq i \leq n - 1 $ ) in the array $ a $ after Dark replaces all missing elements with $ k $ .

Dark should choose an integer $ k $ so that $ m $ is minimized. Can you help him?

## 说明/提示

In the first test case after replacing all missing elements with $ 11 $ the array becomes $ [11, 10, 11, 12, 11] $ . The absolute difference between any adjacent elements is $ 1 $ . It is impossible to choose a value of $ k $ , such that the absolute difference between any adjacent element will be $ \leq 0 $ . So, the answer is $ 1 $ .

In the third test case after replacing all missing elements with $ 6 $ the array becomes $ [6, 6, 9, 6, 3, 6] $ .

- $ |a_1 - a_2| = |6 - 6| = 0 $ ;
- $ |a_2 - a_3| = |6 - 9| = 3 $ ;
- $ |a_3 - a_4| = |9 - 6| = 3 $ ;
- $ |a_4 - a_5| = |6 - 3| = 3 $ ;
- $ |a_5 - a_6| = |3 - 6| = 3 $ .

So, the maximum difference between any adjacent elements is $ 3 $ .

## 样例 #1

### 输入

```
7
5
-1 10 -1 12 -1
5
-1 40 35 -1 35
6
-1 -1 9 -1 3 -1
2
-1 -1
2
0 -1
4
1 -1 3 -1
7
1 -1 7 5 2 -1 5```

### 输出

```
1 11
5 35
3 6
0 42
0 0
1 2
3 4```

# 题解

## 作者：JS_TZ_ZHR (赞：4)

这题的确考验思维。

一开始，我以为要取所有的确定的数的平均值，样例过了，WA了。

接下来，我只取在不确定的数旁边的确定的数的平均值，样例过了，WA了。

~~样例真弱~~

思考一下，首先，代替缺失的数的数为正整数，并且，对答案可能有新的影响的数只有缺失的数的数和他旁边的数。

我们来看一个例子：

$5$

$1，-1，2，-1，3，-1，9$

可以看出，$k$取$5$最优，这时，影响答案的只有$1$和$9$这两个缺失的数旁边的**最值**产生了影响。

于是，我们可以得到代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[1000005],Max,Min,k,ans;
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);//输入 
		Max=-1,Min=2e9;//初始化 
		a[n+1]=0;//防HACK 
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		for(int i=1;i<=n;i++){
			if(a[i]!=-1&&(a[i-1]==-1||a[i+1]==-1)){//取最值 
				Max=max(Max,a[i]);
				Min=min(Min,a[i]);
			} 
		}
		k=(Max+Min)>>1;//k=(min+max)/2
		for(int i=1;i<=n;i++){
			if(a[i]==-1)a[i]=k;
			if(i!=1)ans=max(ans,abs(a[i]-a[i-1]));//记录答案 
		}
		printf("%d %d\n",ans,k);
		ans=k=0;//清空 
	}
	return 0; 
}
```
注意：即使不是缺失的数也有可能对答案造成贡献

---

## 作者：liqiqi (赞：2)

这题一开始就想到贪心，取平均值，但是一直wa了。

想到区间最优解可以使用三分法，找到这个长度最小值，从0到n三分填充数字k的大小，得到最优解。
```c
#include<bits/stdc++.h>
using namespace std;
long long a[1000000];
int m;
long long tt = 1e9;//tt记录长度最小值
inline long long read()
{
	long long x = 0; bool s = 0; char ch = 0;
	while (!isdigit(ch)) { s |= (ch == '-'); ch = getchar(); }
	while (isdigit(ch)) { x = (x << 1) + (x << 3) + (ch - 48); ch = getchar(); }
	return s ? -x : x;
}
long long check(long long x)
{
	long long ans = 0;
	for (int i = 0; i < m-1; i++)
	{
		int q, w;
		if (a[i] < 0)
			q = x;
		else
			q = a[i];
		if (a[i + 1] < 0)
			w = x;
		else
			w = a[i + 1];
		ans = max(ans, (long long )abs(q - w));
	}
	tt = min(tt, ans);
	return ans;
}
long long dfs(long long l, long long r)
{
	while (r - l > 1)//当r和l相差为一时结束循环
	{
		long long lmid = l+r>>1;//lmid为左区间
		long long rmid = lmid + r >> 1;//rmid为右区间
		if (check(lmid) < check(rmid))
			r = rmid;
		else 
			l = lmid;
	
		
	}
	return check(l) < check(r) ? l : r;//最后判断一下l,r哪个更小
}
int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		
		cin >> m;
		tt = 1e9;
		long long mx = 0;
		for (int i = 0; i < m; i++)
		{
			long long h;
			h = read();
			a[i] = h;
			if (a[i] > mx)//找到右边界最大值
				mx = a[i];
		}
			
		long long k=dfs(0, mx);
		cout << tt << " " << k << endl;
	}
}
```


---

## 作者：Anita_Hailey (赞：1)

## T2 [Motarack's Birthday](http://codeforces.com/contest/1301/problem/B)

其实这个题挺坑的。。WA了2次，又掉rating了。。。。

我这题的想法想到了平均。。。但其实不是。。应该是一个中位数。。。

准确的说。我们先找出没有丢的相邻数之差的最大绝对值，然后对于每一个pair$<a_i,-1>$，其中$a_i$!=-1,进行关于$a_i$的排序，找到这些询问的中位数，

最后绝对值的最大值应该拿中位数根两边的比一下，在跟已知的最大值比一下即可。最后 k即为这个中位数

还要特判，就是全是-1的时候直接输出0 0

```c++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <stack>
#include <map>
#include <queue>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
#define fake int
using namespace std;
int read(){
	int x=0;bool f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=1;
		ch=getchar();
	}
	while(ch<='9'&&ch>='0'){
		x=(x<<1)+(x<<3)+(ch-'0');
		ch=getchar();
	}
	return f?-x:x;
}
char Get(){
	char ch=getchar();
	while(ch==' '||ch=='\r'||ch=='\n') ch=getchar();
	return ch;
}
const int Maxn=1e5+111;
ll n,k,t,a[Maxn],max1;
struct Node{
	ll f,s;
}p[Maxn];
bool flag;
bool cmp(Node a,Node b){
	return a.s<b.s;
}
int main(){
//	freopen("ret.in","r",stdin);
	t=read();
	while(t--){
		n=read();bool flag=0;a[0]=0;
		for(int i=1;i<=n;i++) {
			a[i]=read();
			if(a[i]!=-1) flag=1;
		}a[n+1]=0;
		if(!flag){
			printf("0 0\n");
			continue;
		}
		max1=0;
		for(int i=1;i<n;i++)
			if(a[i]!=-1&&a[i+1]!=-1) max1=max(max1,abs(a[i]-a[i+1]));
		int cnt=0;
		for(int i=1;i<n;i++){
			if(!((a[i]!=-1&&a[i+1]!=-1)||(a[i]==-1&&a[i+1]==-1))){
				p[++cnt].f=-1;
				p[cnt].s=max(a[i],a[i+1]);
			}
		}
		sort(p+1,p+1+cnt,cmp);
		ll pp=(p[1].s+p[cnt].s)/2;
		printf("%lld %lld\n",max(p[cnt].s-pp,max(max1,pp-p[1].s)),pp);
	}
	return 0;
}

```


---

## 作者：123456zmy (赞：1)

题意：  
给你一个序列，其中有部分元素缺失，你需要把缺失的元素全部更改为一个值，并使相邻两元素最大的差的绝对值（$|a_i-a_{i-1}|$）最小。输出这个值和此时缺失的元素的值。
___
影响答案的是在缺失元素旁边的数的最大值和最小值，记录一下到最后输出即可。固定的数之间的差的绝对值也要计入答案。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100011],ansl,ansr,ansm;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		ansl=0x3f3f3f3f;
		ansr=0;ansm=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		for(int i=2;i<n;i++)if(a[i]==-1)
		{
			ansl=min(ansl,min(a[i-1]==-1?0x3f3f3f3f:a[i-1],a[i+1]==-1?0x3f3f3f3f:a[i+1]));
			ansr=max(ansr,max(a[i-1],a[i+1]));
		}
		else if(a[i-1]!=-1)ansm=max(ansm,abs(a[i]-a[i-1]));
		if(a[1]==-1&&a[2]!=-1)ansl=min(ansl,a[2]),ansr=max(ansr,a[2]);
		if(a[n]==-1&&a[n-1]!=-1)ansl=min(ansl,a[n-1]),ansr=max(ansr,a[n-1]);
		if(a[n]!=-1&&a[n-1]!=-1)ansm=max(ansm,abs(a[n]-a[n-1]));
		if(ansl==0x3f3f3f3f)ansl=0;
		printf("%d %d\n",max(ansm,(ansr-ansl+1)>>1),ansl+ansr>>1);
	}
	return 0;
}
```

---

## 作者：Ryan_Adam (赞：0)

# CF1301D Time to Run 题解
思维题。
## 分析
把一个格子视作一个点，每个点的度数都是偶数，所以这是一张欧拉图。而需要走遍整个方格图，可以证明只要 $k$ 不超过 $4nm-2n-2m$ 就一定有解。

很明显存在很多种方案，这里我用的方案是：从左上角出发，向右走 $m-1$ 步到头，再向左走 $m-1$ 步回来，向下走一步。重复以上步骤，直到走到左下角。然后向右走一步，向上走 $n-1$ 步到头，向下走 $n-1$ 步回来。重复上面步骤，直到走到右下角。这时候你会发现你已经走完了这张网格图里的所有边。注意在走的过程中如果步数用完了中断输出答案即可。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Raiden
{
    int const N = 3005;
    int n, m, k, num[N], cnt;
    char ans[N][5];
    signed work()
    {
        cin >> n >> m >> k;
        if (k > 4 * n * m - 2 * n - 2 * m)return cout << "NO" << endl, 0;
        int anss = 0, sum = k;
        cout << "YES" << endl;
        while (k)
        {
            int _min;
            if (sum - k < m - 1)
            {
                _min = min(k, m - 1);
                num[++cnt] = _min;
                ans[cnt][0] = 'R';
            }
            else if (sum - k < 2 * (m - 1))
            {
                _min = min(k, m - 1);
                num[++cnt] = _min;
                ans[cnt][0] = 'L';
            }
            else if (sum - k < 2 * (m - 1) + 1)
            {
                _min = 1;
                num[++cnt] = _min;
                ans[cnt][0] = 'D';
            }
            else if (sum - k >= 4 * n * m - 2 * n - 2 * m - (n - 1))
            {
                cnt++;
                _min = min(k, n - 1);
                num[cnt] = _min;
                ans[cnt][0] = 'U';
            }
            else if (anss % 3 == 0)
            {
                _min = min(k, m - 1);
                if (_min)
                {
                    cnt++;
                    num[cnt] = _min;
                    ans[cnt][0] = 'R';
                }
                anss++;
            }
            else if (anss % 3 == 1)
            {
                _min = min(k, 3 * (m - 1));
                int __min = _min / 3;
                if (__min)
                {
                    cnt++;
                    num[cnt] = __min;
                    ans[cnt][0] = 'U';
                    ans[cnt][1] = 'D';
                    ans[cnt][2] = 'L';
                }
                if (_min % 3 == 1)
                {
                    num[++cnt] = 1;
                    ans[cnt][0] = 'U';
                }
                if (_min % 3 == 2)
                {
                    num[++cnt] = 1;
                    ans[cnt][0] = 'U';
                    ans[cnt][1] = 'D';
                }
                anss++;
            }
            else
            {
                _min = 1;
                num[++cnt] = _min;
                ans[cnt][0] = 'D';
                anss++;
            }
            k -= _min;
        }
        cout << cnt << endl;
        for (int i = 1; i <= cnt; i++)cout<< num[i] << " " << ans[i] << endl;
        return 0;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return Raiden::work();
}
```

---

