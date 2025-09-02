# Colorful Points

## 题目描述

You are given a set of points on a straight line. Each point has a color assigned to it. For point $ a $ , its neighbors are the points which don't have any other points between them and $ a $ . Each point has at most two neighbors - one from the left and one from the right.

You perform a sequence of operations on this set of points. In one operation, you delete all points which have a neighbor point of a different color than the point itself. Points are deleted simultaneously, i.e. first you decide which points have to be deleted and then delete them. After that you can perform the next operation etc. If an operation would not delete any points, you can't perform it.

How many operations will you need to perform until the next operation does not have any points to delete?

## 说明/提示

In the first test case, the first operation will delete two middle points and leave points "ab", which will be deleted with the second operation. There will be no points left to apply the third operation to.

In the second test case, the first operation will delete the four points in the middle, leaving points "aa". None of them have neighbors of other colors, so the second operation can't be applied.

## 样例 #1

### 输入

```
aabb
```

### 输出

```
2
```

## 样例 #2

### 输入

```
aabcaa
```

### 输出

```
1
```

# 题解

## 作者：万弘 (赞：5)

这其实是个暴力题

如果按题意模拟,至多进行$\mathcal O(n)$次操作,每次操作需要$\mathcal O(n)$的代价计算,总时间复杂度是$\mathcal O(n^2)$无法接受.

考虑将相邻的同色点划分为一组,有$cnt$组,第$i$组的大小是$size(i)$

- 对于两端的组:其最右侧/最左侧的点会被删除,$size(i)-1$
- 对于其它组:最右侧和最左侧的点都会被删除$size(i)-2$(当点只有$1$个的时候只能$-1$了)
 
这样删完之后,把点数为0的组去掉,然后把相邻的同色组合并.

重复上述步骤,直到$cnt\le 1.$  
显然这样一次操作的代价是$\mathcal O(cnt)$,并删除了$\mathcal O(cnt)$个点.因为点是$\mathcal O(n)$个,所以总时间复杂度是$\mathcal O(n).$

```cpp
/**********/
#define MAXN 1000011
char a[MAXN],c[MAXN];
ll size[MAXN];
int main()
{
    scanf("%s",a+1);
    ll n=strlen(a+1),cnt=0,ans=0;
    for(ll i=1;i<=n;++i)//分组
        if(a[i]==c[cnt])++size[cnt];
        else c[++cnt]=a[i],size[cnt]=1;
    while(cnt>1)
    {
        for(ll i=1;i<=cnt;++i)//删除两端的点,调整size
            if(i==1||i==cnt)--size[i];
            else size[i]-=2;
        ll cur=0;
        for(ll i=1;i<=cnt;++i)
        {
            if(size[i]<=0)continue;
            if(c[i]==c[cur])size[cur]+=size[i];//合并
            else c[++cur]=c[i],size[cur]=size[i];
        }
        ++ans;cnt=cur;
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Jin_Yichen (赞：1)

看到题：不愧是蓝题，难搞！

看到数据范围：不会还要用什么我不会的高级算法吧……

~~忍不住看了一眼题解：三位大佬牛逼，被骗了。~~

## 思路 ：
我们可以把相邻的同色节点划分成一组，共 $x$ 组，每一组长度为 $siz_i$。

分组讨论每一种情况：

- 对于第一组，其最右侧的节点会被删除，$siz_i-1$。
- 对于最后一组，其最左侧的节点会被删除，$siz_i-1$。
- 对于中间的组，其两侧的节点都会被删除，$siz_i-2$；当已经删除一个节点时，就只能删除一个了，$siz_i-1$。

删完一轮后，把长度为0的组删除，把剩余的组合并。

重复步骤，直到 $x\le1$。

因为每个点都要删除一遍，点的个数为 $n$ 个，所以时间复杂度是 $\varTheta(n)$。
## CODE：
```cpp
#include<bits/stdc++.h>
const int N=1000005;
char a[N],ch[N];//a为输入字符串，ch为每一组的字符
long long siz[N],x,ans;//不开long long见祖宗
int main(){
	scanf("%s",a+1);//从第一位开始输入
	long long len=strlen(a+1);//同样从第一位开始计算
	for(int i=1;i<=len;i++){
		if(a[i]==ch[x])siz[x]++;//满足要求就组数长度+1
		else ch[++x]=a[i],siz[x]=1;//否则就重新增加一组
	}
	while(x>1){//如果组数>1就一直操作
		for(int i=1;i<=x;i++){
			if(i==1||i==x)siz[i]--;//如果这是两边的组，就只删除一个数
			else siz[i]-=2;//如果是中间的，就删除两个数
		}
		long long cnt=0;
		for(int i=1;i<=x;i++){
			if(siz[i]<=0)continue;//如果当前组的长度为0,那么就删除这组（跳过）
			if(ch[i]==ch[cnt])siz[cnt]+=siz[i];//合并组
			else ch[++cnt]=ch[i],siz[cnt]=siz[i];
		}
		ans++,x=cnt;//操作次数+1，调整x为新的组数
	}
	printf("%lld",ans);//输出答案
	return 0;
}
```

---

## 作者：ThomasNO1 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF909D)

## Solution

如果这道题用暴力，时间复杂度是 $O(n^2)$ 的复杂度，无法通过这一道题，只能用 $O(n)$ 左右的复杂度，此时 STL 库就起到了作用。

我们可以发现，这个字符串中的一些相同且两两相邻的字符可以组成一个块，像这样：

$\texttt{aafeooooie}$ 分割成 $\texttt{aa|f|e|oooo|i|e}$。

所以这些块，可以用一个 `vector` 来存储这些块。`vector` 则存储这一个 `pair<char,int>` 表示，一个以一个 `char` 类型的字符开头的的一个块的长度。而这个 `vector` 的属性是第 $i-1$ 次消除时，剩下的字符串所生成的新块。

我们可以发现，一个块，如果他是这个字符串中第一个块，那消除时，那只有这个块的最右边的那个字符才会和在这个字符的右边与它不同的字符抵消。同理，如果一个块是字符串中倒数第一个块，那消除时，那只有这个块的最左边的那个字符才会和在这个字符的左边与它不同的字符抵消。所以，首尾两个块在每一次抵消时，这个块的字符数量只会减 $1$，而在中间的块们，其首尾两位字符都会被抵消，所以，如果是在中间的块，那这个块的字符数量会减 $2$。

当一个块的字符数量 $\le 0$，那这个块为空，无用，循环直接调到下一次循环当中，不被加到下一层 `vector` 当中。如果这个块不为空，我们还要判断这一个块可不可以和前面一个的已被受消除的块合并，也就是如果这两个块的首字母相同，那就让前面一个的已被受消除的块的字符数量加上此时也被修改的块的字符数量。如果无法合并，也就是两个块的首字母不同，那就让此时的这块块加入到下一轮“淘汰赛”当中。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 8;
vector<pair<char,int> > v[MAXN];//属性见上
char s[MAXN];
int main(){
	scanf("%s",s);
	int len = strlen(s),num = 0;
	for(int i = 0;i < len;i++){//记录刚开始，每个块的首字母与块的大小。
		if(i == 0){
			num++;
			continue;
		}
		if(s[i] != s[i - 1]) v[1].push_back({s[i - 1],num}),num = 1;
		else num++;
	}
	v[1].push_back({s[len - 1],num});//注意，上一个循环中，并没有记录最后一个块的首字母和大小，所以注意这一处。
	int I = 1;
	while(v[I].size() > 1){//如果只有一个或根本没有块了，无法合并，退出
		for(int i = 0;i < v[I].size();i++){//解析见上文
			int number = v[I][i].second;
			if(i == 0 || i == v[I].size() - 1)
				number--;
			else	
				number -= 2;
			if(number <= 0)
				continue;
			if(!v[I + 1].empty()){
				if(v[I + 1][v[I + 1].size() - 1].first ==
				v[I][i].first) v[I + 1][v[I + 1].size() - 1].second += number;
				else
					v[I + 1].push_back({v[I][i].first,number});
			}
			else
				v[I + 1].push_back({v[I][i].first,number});
		}
		I++;
	}
	printf("%d\n",I - 1);//刚开始不算
	return 0;
}
```

---

## 作者：快斗游鹿 (赞：0)

## 思路

模拟题。

显然一个个点模拟会超时，但可以把连续的一段颜色相同的点划分为一组，然后分类讨论：

如果是最左端的一组，把右端点删掉就行。

如果是最右端的一组，把左端点删掉就行。

否则就左右端点一起删掉。

结束条件是只剩一组或全部删光。每次操作后进行一次合并即可，整个过程拿数组模拟就好。总时间复杂度 $O(n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
string s;
int a[N],col[N],size[N],n,cnt,ans;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
int main(){
	cin>>s;n=s.length();
	for(int i=0;i<s.length();i++)a[i+1]=s[i]-'a'+1;
	for(int i=1;i<=n;i++){
		if(a[i]!=a[i-1]){
			size[++cnt]++;col[cnt]=a[i];
		}
		else size[cnt]++;
	}
	while(cnt>1){
		for(int i=1;i<=cnt;i++){
			if(i==1||i==cnt)size[i]--;
			else size[i]-=2;
		}
		int ttt=0;
		int lstcol=0;
		for(int i=1;i<=cnt;i++){
			if(size[i]<=0)continue;
			if(col[i]!=lstcol){
				lstcol=col[i];
				size[++ttt]=size[i];col[ttt]=col[i];
			}
			else{
				size[ttt]+=size[i];
			}
		}
		ans++;cnt=ttt;
	}
	cout<<ans<<endl;
	return 0;
}

```


---

## 作者：_edge_ (赞：0)

一看这题，wc 怎么这么难搞。

看数据范围 $10^6$ 不会又是什么贪心分类讨论吧。。

~~然后瞄了一眼题解，被骗了。~~

首先，把序列相同颜色的段都合并掉。

然后会发现变成了好几段不同颜色的序列。

把每一段颜色看成一个整体，会发现每次前后两个都会被消掉，除非是头和尾巴，做完这些之后，某些颜色块会合并，就暴力合并掉即可。

然后暴力模拟这个过程，发现还挺快的，然后就过了。

让我们来严谨的分析一下这个复杂度。

每一次，我们扫到一个块，至少会把这个块里面的一个元素给拎出去。

而每个块的数量级别只有 $n$，也就是说，你可以把它看成每一次都扫到一个数，然后扔掉它。

至于暴力合并，也可用把它看成上面的过程，会发现和暴力删的是等价的。

另外合并的时候请勿使用 memcpy。

```cpp
// 12:18~12:30
#include <iostream>
#include <cstdio> 
using namespace std;
const int INF=1e6+5;
string s1;
int sz[INF],col[INF],ans,L,col1[INF],sz1[INF];
signed main()
{
	ios::sync_with_stdio(false);
	cin>>s1;int n=s1.size();s1=" "+s1;
	for (int i=1;i<=n;i++) 
		if (s1[i]==s1[i-1]) sz[L]++;
		else ++L,col[L]=s1[i],sz[L]=1;
	while (L>1) {
		for (int i=1;i<=L;i++)
			if (i==1 || i==L) sz[i]--;
			else sz[i]-=2;
		int la=0,sum=0;
		for (int i=1;i<=L;i++) {
			if (sz[i]<=0) continue;
			if (!la || col1[la]!=col[i]) 
				++sum,sz1[sum]=sz[i],col1[sum]=col[i],la=sum;
			else sz1[sum]+=sz[i];
		}
		L=sum;ans++;
		for (int i=1;i<=L;i++)
			sz[i]=sz1[i],col[i]=col1[i];
	}
	cout<<ans<<"\n";
	return 0;
}
```


---

