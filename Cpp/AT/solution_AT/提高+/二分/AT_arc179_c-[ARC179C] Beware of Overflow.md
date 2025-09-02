# [ARC179C] Beware of Overflow

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc179/tasks/arc179_c

この問題は**インタラクティブな問題**（あなたの作成したプログラムとジャッジシステムが入出力を介して対話を行う形式の問題）です.

正整数 $ N $ が与えられます.

ジャッジシステムは正整数 $ R $ および $ N $ 個の整数 $ A_1,A_2,\dots\ ,A_N $ を隠し持っています. ここで $ |A_i|\le\ R,\ \left|\displaystyle\sum_{i=1}^{N}A_i\right|\ \le\ R $ を満たすことが保証されます.

絶対値が $ R $ 以下の整数しか書き込むことができない黒板があり, はじめは何も書き込まれていません.

ジャッジシステムは, 黒板に $ A_1,A_2,\ \dots\ ,A_N $ の値を **この順で** 書き込みました. あなたは, 黒板にただ $ 1 $ つの値 $ \displaystyle\sum_{i=1}^{N}A_i $ が書き込まれている状態にする必要があります.

あなたは $ R $ および $ A_i $ の値を直接知ることはできませんが, その代わりにジャッジシステムに対して次のやり取りを $ 25000 $ 回まで行うことができます.

正整数 $ i $ について, $ i $ 番目に黒板に書き込まれた整数を $ X_i $ とします. 特に, $ i=1,2,\dots\ ,N $ について $ X_i=A_i $ です.

$ 1 $ 回のやり取りでは, 相異なる正整数 $ i,j $ を指定し, 次のいずれかを選んで行います.

- 足し算をしてもらう. ジャッジシステムは黒板から $ X_i,X_j $ を消し, 新たに $ X_i+X_j $ の値を黒板に書き込む.
  - $ |X_i+X_j|\le\ R $ を満たしていなくてはならない.
- 大小比較をしてもらう. ジャッジシステムは $ X_i\lt\ X_j $ の真偽を答える.

ただし, 各やり取りを始める時点で $ i,j $ 番目に黒板に書き込まれた整数がすでに黒板から消されていてはなりません.

適切にやり取りを行って, 全てのやり取りを終えた後に黒板にただ $ 1 $ つの値 $ \displaystyle\sum_{i=1}^{N}A_i $ が書き込まれている状態にしてください.

$ R $ および $ A_i $ はプログラムとジャッジシステムの対話の開始前に決定されます.

### Input &amp; Output Format

この問題はインタラクティブな問題（あなたの作成したプログラムとジャッジシステムが入出力を介して対話を行う形式の問題）です.

最初に, $ N $ を標準入力から受け取ってください.

> $ N $

次に, 黒板にただ $ 1 $ つの値 $ \displaystyle\sum_{i=1}^{N}A_i $ が書かれている状態になるまで, やり取りを繰り返してください.

足し算をしてもらうときは, 以下の形式で標準出力に出力してください. 末尾に改行を入れてください. ここで $ i,j $ は相異なる正整数です.

> + $ i $ $ j $

これに対するジャッジシステムの応答は, 次の形式で標準入力から与えられます.

> $ P $

ここで $ P $ は整数で,

- $ P\geq\ N+1 $ の場合は, $ X_i+X_j $ の値が黒板に書き込まれ, それが $ P $ 番目に書き込まれたことを表します.
- $ P=-1 $ の場合は, $ i,j $ が制約を満たしていないか, やり取りの回数が $ 25000 $ 回を超えたことを表します.

大小比較をしてもらうときは, 以下の形式で標準出力に出力してください. 末尾に改行を入れてください. ここで $ i,j $ は相異なる正整数です.

> ? $ i $ $ j $

これに対するジャッジシステムの応答は, 次の形式で標準入力から与えられます.

> $ Q $

ここで $ Q $ は整数で,

- $ Q=1 $ の場合は, $ X_i\ <\ X_j $ が真であることを表します.
- $ Q=0 $ の場合は, $ X_i\ <\ X_j $ が偽であることを表します.
- $ Q=-1 $ の場合は, $ i,j $ が制約を満たしていないか, やり取りの回数が $ 25000 $ 回を超えたことを表します.

足し算をしてもらうやり取りおよび大小比較をしてもらうやり取りのいずれについても, ジャッジシステムの応答が $ -1 $ であった場合は, プログラムはすでに不正解とみなされています. この場合, ただちにプログラムを終了してください.

黒板にただ $ 1 $ つの値 $ \displaystyle\sum_{i=1}^{N}A_i $ が書かれている状態になったら, 以下の形式でそのことをジャッジシステムに報告してください. ただし, これはジャッジシステムとのやり取りの回数に計上されません. その後, ただちにプログラムを終了してください.

```
!
```

上記のいずれの形式にも当てはまらない出力を行った場合は, `-1` が標準入力から与えられます.

```
-1
```

このときも, プログラムはすでに不正解とみなされています. ただちにプログラムを終了してください.

## 说明/提示

### 制約

- $ 2\leq\ N\leq\ 1000 $
- $ 1\leq\ R\leq\ 10^9 $
- $ |A_i|\leq\ R $
- $ \left|\displaystyle\sum_{i=1}^{N}A_i\right|\ \le\ R $
- $ N,R,A_i $ は整数.

### 注意点

- **出力を行うたびに, 末尾に改行を入れて標準出力を flush してください. そうしなかった場合, ジャッジ結果が TLE となる可能性があります.**
- 解答を出力したら（または `-1` を受け取ったら）ただちにプログラムを終了してください. そうしない場合, ジャッジ結果は不定です.
- 余計な改行は不正なフォーマットの出力とみなされることに注意してください.

### 入出力例

$ N=3,R=10,A_1=-1,A_2=10,A_3=1 $ のときの対話の一例を示します.

入力出力説明`3`まず整数 $ N $ が与えられます。`? 1 2`大小比較をしてもらいます.`1`$ X_1\lt\ X_2\ (-1\lt\ 10) $ なのでジャッジシステムは $ 1 $ を返します. `+ 1 3`足し算をしてもらいます.`4`ジャッジシステムは $ X_1=-1,X_3=1 $ を黒板から消し, $ X_1+X_3=0 $ の値を黒板に書き込みました. $ 4 $ 番目の書き込みでした.`+ 2 4`足し算をしてもらいます.`5`ジャッジシステムは $ X_2=10,X_4=0 $ を黒板から消し, $ X_2+X_4=10 $ の値を黒板に書き込みました. $ 5 $ 番目の書き込みでした.`!`黒板にはただ $ 1 $ つの値 $ \displaystyle\sum_{i=1}^{N}A_i $ が書き込まれている状態になったので, そのことをジャッジシステムに報告します.

# 题解

## 作者：fcy20180201 (赞：4)

第一次做出来 C 题，写个题解纪念一下（~~虽然没过 B~~）。

## 题意

狡猾的出题人有一个序列，和一个正整数 $R$，满足**数组里每一项的绝对值**和**数组总和的绝对值**都 $\le R$。但他只告诉了你数组的长度 $N$。

现在你可以执行不超过 $25000$ 次操作，每次操作都是以下两种形式之一：

1. 从数组里选两个数，删掉它们，再加入它们的和，并要保证这个和的绝对值 $\le R$。

2. 从数组里选两个数，**立即**得到它们的大小关系。

狡猾的出题人要求你执行完操作后使数组里只剩一个数。求怎么操作。

## 思路

既然每次将两个数合并时要保证这个和 $\le R$，那么其实本题的关键就是找出两个**固定的位置（这个位置可能是常数也可能和数组长度有关系）**，在任意一个满足题目中条件的数组中，这两个位置上的数的和的绝对值一定 $\le R$。

首先肯定是将数组排序。然后这两个位置无非就是最中间的两个数或者第一个数和最后一个。如果取中间的两个，有这样一组 Hack 数据：$x$ 个 $-1$ 和 $x+1$ 个 $1$（或者个数交换一下），如果把 $R$ 设为 $1$，那么最中间两个数的和 $2$ 或 $-2$ 就不符合条件了。

如果取最小和最大的，似乎找不到反例，那就证明一下。

- 如果数组里的数全部非正或非负，不妨全转化为非负，那么两边两个数的和一定 $\le$ 数组的总和 $\le R$。

- 如果有正有负，那么最小的是负数，最大的是正数。正数加负数小于正数也大于负数，绝对值还是 $\le R$。

得证！

于是每次执行操作 $1$ 时把最小的和最大的取出来加起来塞回去即可。

## 实现方法
排序：因为只能比较大小，所以使用归并排序，时间复杂度和询问次数都是 $\mathcal O(N \log N)$。

缩数组：每次取出两个数后暴力将剩下的数移位，时间复杂度 $\mathcal O(N^2)$，然后二分找到两个数的和插在哪里，时间复杂度和询问次数都是 $\mathcal O(N \log N)$，最后再暴力插入，时间复杂度 $\mathcal O(N^2)$。

所以总时间复杂度 $\mathcal O(N^2)$，询问次数 $\mathcal O(N \log N)$ 次，可过。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p[1005],len,b[1005];
int Query(int l,int r){//比较大小
	printf("? %d %d",l,r);
	cout<<endl;
	int res;scanf("%d",&res);
	if(res==-1)exit(0);
	return res;
}
void Sort(int l,int r){//归并排序
	if(l>=r)return ;
	int mid=(l+r)>>1;
	Sort(l,mid);
	Sort(mid+1,r);
	int tot=0;
	for(int i=l,j=mid+1;i<=mid || j<=r;){
		if(i>mid)b[++tot]=p[j++];
		else if(j>r)b[++tot]=p[i++];
		else{
			int x=Query(p[i],p[j]);
			if(x)b[++tot]=p[i++];
			else b[++tot]=p[j++];
		}
	}
	for(int i=l;i<=r;i++)p[i]=b[i-l+1];
	return ;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)p[i]=i;
	Sort(1,n);
	len=n;
	for(int i=1;i<n;i++){//缩数组
		printf("+ %d %d",p[1],p[len]);
		cout<<endl;
		int res;scanf("%d",&res);
		if(res==-1)return 0;
		for(int j=2;j<len;j++)p[j-1]=p[j];
		int l=1,r=len-1;
		while(l<r){
			int mid=(l+r)>>1;
			if(Query(p[mid],res))l=mid+1;
			else r=mid;
		}
		for(int j=len-2;j>=l;j--)p[j+1]=p[j];
		p[l]=res,len--;
	}
	cout<<'!'<<endl;
	return 0;
}

```

---

## 作者：Moya_Rao (赞：1)

~~第一次接触互动问题……~~

# 思路

考虑先用 sort 排个序，在排序中的 cmp 里执行第二种交互，也就是询问。大概要用掉 $N \log N$ 次交互机会。

接着我们选择最大的值和最小的值进行相加，因为最大的值和最小的值的和一定满足它的条件。

## 证明

若它们都是正数或都是负数的话，显而易见是满足的，因为题目保证了所有的数字的和的绝对值都满足条件。

若它们一个是负数，一个是正数的话，它们一定会抵消一部分。又因为题目保证了每个数字的绝对值都是满足的，那么抵消了一部分后就不可能不满足了。

------------

我们让最大值和最小值相加后，会出现一个新的值。为了让交互次数尽量的少，肯定不能再用 sort 全部排一次序，次数肯定会超；也不能逐个去比较后再插入，次数还是不够；只能运用二分来找到这个新数值的插入位置，再 $O(N)$ 插入。

这样做，交互次数会是 $2 \times N \log N$ 次，细算下来，是 $20000$ 次左右。题目给出的限制是 $25000$ 次，没问题。

时间复杂度吧，只要 $O(N \log N + N^2 \log N)$ 就行，其实就可以看作 $O(N^2 \log N)$ 嘛。

# 代码

要记得注意一下输入输出的格式哈~

```
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+5;
int n,l,r,p[N],a,b,k,kk,ll,rr,s;
bool cmp(int x,int y){
    printf("? %d %d\n",x,y);
    fflush(stdout);
    scanf("%d",&kk);
    return kk==1?1:0;
}
void Insert(int m,int o){
    r++;
    for(int i=r;i>m;i--)p[i]=p[i-1];
    p[m]=o;
}
int main(){
    scanf("%d",&n);
    l=1,r=n;
    for(int i=1;i<=n;i++)p[i]=i;
    sort(p+1,p+n+1,cmp);
    n--;
    while(n--){
        a=p[l],b=p[r];l++,r--;
        printf("+ %d %d\n",a,b);
        fflush(stdout);
        scanf("%d",&k);
        ll=l,rr=r,s=r+1;
        while(ll<=rr){
            int mid=(ll+rr)/2;
            if(cmp(k,p[mid]))s=mid,rr=mid-1;
            else ll=mid+1;
        }
        Insert(s,k);
    }
    printf("!\n");
    fflush(stdout);
    return 0;
}
```

[提交记录](https://atcoder.jp/contests/arc179/submissions/54787308)

---

## 作者：fydj (赞：1)

### 思路

可以先把所有的 $A$ 排个序，可以使用归并排序，比较次数 $O(n\log n)$。

然后最小的加上最大的，一定可以符合条件：

如果同正或同负，因为所有数之和的绝对值小于等于 $R$，两端的数之和的绝对值也一定小于等于 $R$；

否则，一正一负的绝对值小于等于 $R$，加起来绝对值也一定小于等于 $R$。

每一次加入一个新的数就二分一个位置，把新的数插入进去，次数也是 $O(n\log n)$。

加起来，总比较次数是 $O(2n\log n)$，大约是 $2000$，可以过。

### 一种优化

记录一下已经比较的两个数和比较的结果，如果这次要比较的两个数已经比较了，那么就直接把结果返回，但作用不大。

### 额外的优化

传递闭包，如果 $a<b$，$b<c$，那么 $a<c$​。

### 代码

```cpp
map<pii,bool> has={};
bool ask(int x,int y) {
	if(x==y) return false;
	if(has.count(make_pair(x,y))) return has[make_pair(x,y)];
	cout<<"? "<<x<<" "<<y<<endl; cout.flush();
	int v; cin>>v;
	has[make_pair(x,y)]=v;
	has[make_pair(y,x)]=!v;
	return v;
}
void merge_sort(int l,int r) {
	if(l==r) return ;
	int mid=l+r>>1;
	merge_sort(l,mid);
	merge_sort(mid+1,r);
	int i,pa,pb;
	va[0]=0; for(i=l;i<=mid;++i) va[++va[0]]=p[i];
	vb[0]=0; for(i=mid+1;i<=r;++i) vb[++vb[0]]=p[i];
	for(i=l,pa=pb=1;i<=r;++i) {
		if(pa<=va[0]&&(pb>vb[0]||ask(va[pa],vb[pb])))
			p[i]=va[pa++];
		else p[i]=vb[pb++];
	}
	return ;
}
void del(int x) {
	int i;
	for(i=1;i<list[0];++i) swap(list[i],list[i+1]);
	--list[0];
	return ;
}
void ins(int x,int p) {
	int i;
	for(i=list[0];i>x;--i) swap(list[i+1],list[i]);
	list[x+1]=p; ++list[0]; return ;
}
int main()
{
	int i,np,l,r,mid,ans;
	cin>>n;
	for(i=1;i<=n;++i) p[i]=i;
	merge_sort(1,n);
	for(i=1;i<=n;++i) list[++list[0]]=p[i]; np=n;
	while(list[0]>1) {
		cout<<"+ "<<list[1]<<" "<<list[list[0]]<<endl; cout.flush();
		cin>>np,--list[0],del(1);
		if(!list[0]) break;
		l=1,r=list[0],ans=0;
		while(l<=r) {
			mid=l+r>>1;
			if(ask(list[mid],np)) ans=max(ans,mid),l=mid+1;
			else r=mid-1;
		}
		ins(ans,np);
	}
	cout<<"!"<<endl; cout.flush();
	return 0;
}
```

---

## 作者：a_sad_soul (赞：1)

看到这个数据范围，显然的，我们需要用到快速排序先让数组变得有序。然后约束条件我们每次取有序序列中最大的和最小的，得到的新数用二分查找插入重复此过程知道数组内元素仅剩最多一个即可。

这个过程可以直接使用 STL 大法， 避免写这么多代码。

```cpp 
#include<bits/stdc++.h>
using namespace std;
bool Cmp(int a,int b){
    printf("? %d %d\n",a,b);fflush(stdout);
    int x=0;scanf("%d",&x);
    return x;
}
int ask(int a,int b){
    printf("+ %d %d\n",a,b);fflush(stdout);
    int pos;scanf("%d",&pos);
    return pos;
}
deque<int>q;
int n;

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)q.push_back(i);
    sort(q.begin(),q.end(),Cmp);
    while(q.size()>1){
        int x=q.front(),y=q.back();q.pop_front(),q.pop_back();
        int mid=ask(x,y);
        q.insert(lower_bound(q.begin(),q.end(),mid,Cmp),mid);
    }
    printf("!\n");
    fflush(stdout);
    return 0;
}

```

---

## 作者：ran_qwq (赞：1)

先把 $a$ 排个序，花费 $n\log n$ 次操作。

重复以下操作直到 $a$ 大小为 $1$：

+ 求 $a$ 中最小的数 $mn$ 与最大的数 $mx$ 之和，并擦掉这两个数。显然不会超出范围。证明：
	+ 根据题目条件，$|mn|\le r$，$|mx|\le r$，并且 $|\sum a_i|\le r$。
   + 如果 $mn$ 和 $mx$ 同号或有一个以上为 $0$，则 $|mn+mx|\le|\sum a_i|\le r$。
   + 否则 $mn<0,mx>0$。
     + 如果 $|mn|\le|mx|$，则 $|mn+mx|=mn+mx<mx\le r$。
     + 否则 $|mn|>mx$，则 $|mn+mx|=-mn-mx\le-mx\le r$。
+ 将结果 $res$ 二分一个位置插入，保证 $a$ 仍有序，单次花费 $\log n$ 次操作。

一共 $2n\log n$ 次操作，大约是 $20000$ 次。

```cpp
int n,siz,a[N],b[N],c[N],d[N];
bool cmp(int x,int y) {if(x==y) return 0; printf("? "),wr(x," "),wr(y,"\n"),fflush(stdout); return rd();}
int add(int x,int y) {printf("+ "),wr(x," "),wr(y,"\n"),fflush(stdout); return rd();}
void QwQ() {
	n=siz=rd(),srand(time(0)); for(int i=1;i<=n;i++) a[i]=i; sort(a+1,a+1+n,cmp);
	for(int t=1;t<n;t++) {
		int cur=add(a[1],a[siz]); siz--;
		for(int i=2;i<=siz;i++) a[i-1]=a[i]; int l=1,r=siz-1,mid;
		while(l<=r) mid=l+r>>1,cmp(cur,a[mid])?r=mid-1:l=mid+1;
		for(int i=siz;i>l;i--) a[i]=a[i-1]; a[l]=cur;
	}
	puts("!"),fflush(stdout);
}
```

---

## 作者：_cbw (赞：0)

由于题目只给出各个数的大小关系，可以~猜出~分析出结论：每次选最大数与最小数做加法。

考虑证明。设当前有 $k$ 个数，分别为 $A_1 \le A_2 \le A_3 \le \cdots \le A_k$。

- 当 $A_1 \ge 0$，即所有 $A_i$ 非负，由题目条件，可知 $\sum_{i = 1}^k A_i \le R$，符合题意。
- 当 $A_k \le 0$，即所有 $A_i$ 非正，同上可知符合题意。
- 当 $A_1 < 0 < A_k$，则 $|A_1 + A_k| \le \max \{ |A_1|,|A_k| \} \le R$，符合题意。

综上，该策略正确。

Code:
```cpp
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

inline bool asklt(const int &x, const int &y)
{
    int res;
    cout << "? " << x << ' ' << y << endl;
    cin >> res;
    if (res == -1)
        exit(0);
    return (res == 1);
}
inline int askadd(const int &x, const int &y)
{
    int res;
    cout << "+ " << x << ' ' << y << endl;
    cin >> res;
    if (res == -1)
        exit(0);
    return res;
}

vector<int> vec;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    vec.reserve(n);
    for (int i = 1; i <= n; ++i)
        vec.push_back(i);
    sort(vec.begin(), vec.end(), asklt);
    int u, v, p;
    while (--n)
    {
        u = vec.front(), v = vec.back();
        vec.pop_back(), vec.erase(vec.begin());
        p = askadd(u, v);
        vec.insert(lower_bound(vec.begin(), vec.end(), p, asklt), p);
    }
    cout << "!\n";
    return 0;
}
```

---

## 作者：I_will_AKIOI (赞：0)

很好的交互题。

首先我们需要保证选择相加的两个数的绝对值 $<R$，很容易想到把最大值和最小值相加，证明如下：

+ 若 $A$ 均为正数且最大值加最小值的绝对值 $\ge R$，由于 $A$ 均为正数，既然最大值加最小值的都 $\ge R$ 了，那么 $A$ 的和也 $\ge R$ 了，与题意矛盾。

+ 若 $A$ 有负有正且最大值加最小值的绝对值 $\ge R$，由于 $\forall i\in[1,n],|A_i|<R$，因此这两个数的和的绝对值也 $<R$，不存在他们的和 $\ge R$ 的情况。

+ 若 $A$ 均为负数且最大值加最小值的绝对值 $\ge R$，由于 $A$ 均为负数，因此最大值加最小值 $\le -R$。既然最大值加最小值的都 $\le -R$ 了，那么 $A$ 的和也 $\le -R$ 了，与题意矛盾。

因此把最大值和最小值相加的绝对值不会 $\ge R$。所以我们先给 $A$ 排个序，每次把最大值和最小值相加，再二分把新得到的数插入到 $A$ 中，不断循环即可。

这里排序我们可以直接写一个 cmp 函数，内容就是询问两个数的大小关系并返回结果。注意直接用 sort 比较次数的常数可能很大，因此要手写归并排序，询问次数可以稳定在 $n\log n$，每次插入二分，一共询问 $n\log n$ 次，总询问次数为 $n\log n$，时间复杂度 $O(n^2)$，可以通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t[1005];
vector<int>v;
bool cmp(int x,int y)
{
	int res;
	cout<<"? "<<x<<" "<<y<<endl;
	cin>>res;
	return res;
}
void sort(int l,int r)
{
	if(l==r) return;
	int mid=(l+r)>>1;
	sort(l,mid);
	sort(mid+1,r);
	int i=l,j=mid+1,k=l;
	while(i<=mid&&j<=r)
	{
		if(cmp(v[i],v[j])) t[k++]=v[i++];
		else t[k++]=v[j++];
	}
	while(i<=mid) t[k++]=v[i++];
	while(j<=r) t[k++]=v[j++];
	for(int i=l;i<=r;i++) v[i]=t[i];
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	cin>>n;
	v.resize(n+1);
	for(int i=1;i<=n;i++) v[i]=i;
	sort(1,n);//对数组进行排序，这里选用vector是因为方便插入
	while(n>1)
	{
		cout<<"+ "<<v[1]<<" "<<v[n]<<endl;
		v.erase(v.begin()+n);
		v.erase(v.begin()+1);
		//删除最大值和最小值
		n-=2;
		int pos;
		cin>>pos;
		int l=1,r=n+1,mid;
		while(l<r)//二分插入位置
		{
			mid=(l+r)>>1;
			if(cmp(v[mid],pos)) l=mid+1;
			else r=mid;
		}
		v.insert(v.begin()+l,pos);//插入新的数字
		n++;
	}
	cout<<"!"<<endl;
	return 0;
}
```

---

## 作者：CodingOIer (赞：0)

## [ARC179C] Beware of Overflow 题解

### 思路分析

题目给出了我们 $2$ 种交互方式：

- `+ x y` 将 $a_z \gets a_x + a_y$，返回 $z$。
- `? x y` 返回 $a_x < a_y$。

对于第二种操作，可以视为给了我们一个比较函数，如下：

```cpp
bool cmp(int x, int y)
{
    printf("? %d %d\n", x, y);
    fflush(stdout);
    int r = 0;
    scanf("%d", &r);
    return r == 1;
}
```

接着，对于 $|a_i| \in [-R, R], |\sum_{i = 1}^{n}a_i| \in [-R, R]$，显然 $a_1 + a_n \in [-R, R]$​，证明如下：

---

$$
a_i \ge 0 \\
S = \sum_{i = 1}^{n}, T = \sum_{i = 2}^{n - 1} \\
\because 0 \le S \le R, a_i \ge 0 \\
\therefore T \le S \\
\because S \le R, T \le S \\
\therefore a_1 + a_n = S - T \le R \\
\because a_i \ge 0 \\
\therefore 0 \le a_1 + a_n \le R \Rightarrow a_1 + a_n \in [-R, R]
$$

---

$$
a_i \le 0 \\
S = \sum_{i = 1}^{n}, T = \sum_{i = 2}^{n - 1} \\
\because 0 \ge S \ge -R, a_i \le 0 \\
\therefore T \ge S \\
\because S \ge R, T \ge S \\
\therefore a_1 + a_n = T - S \ge R \\
\because a_i \le 0 \\
\therefore 0 \ge a_1 + a_n \ge R \Rightarrow a_1 + a_n \in [-R, R]
$$

---

$$
a_1 \le 0, a_n \ge 0 \\
\because a_1 \le 0, a_n \ge 0 \\
\therefore |a_1 + a_n| = ||a_1| - |a_n|| \\
\because |a_1| \in [0, R], |a_n| \in [0, R] \\
\therefore ||a_1| - |a_n|| \le R \Rightarrow a_1 + a_n \in [-R, R]
$$

---

所以，$|a_i| \in [-R, R], |\sum_{i = 1}^{n}a_i| \in [-R, R] \Rightarrow |a_1 + a_n| \in [-R, R]$。

我们每次选择最小的数字和最大的数字即可。

随便抓出一只数据结构维护即可。（比较次数不能大于 $\log n$）

但是 $n \le 10^3$，所以我们使用二分后 $O(N)$ 插入即可。

但数据结构可以做到 $n \le 10^5$ 的。

### 代码实现

```cpp
#include <algorithm>
#include <cstdio>
constexpr int MaxN = 1e6 + 5;
int n;
int l, r;
int p[MaxN];
bool cmp(int x, int y)
{
    printf("? %d %d\n", x, y);
    fflush(stdout);
    int r = 0;
    scanf("%d", &r);
    return r == 1;
}
void insert(int x, int y)
{
    r++;
    for (int i = r; i > x; i--)
    {
        p[i] = p[i - 1];
    }
    p[x] = y;
}
int main()
{
    scanf("%d", &n);
    l = 1;
    r = n;
    for (int i = 1; i <= n; i++)
    {
        p[i] = i;
    }
    std::sort(p + 1, p + 1 + n, cmp);
    for (int i = 1; i <= n - 1; i++)
    {
        int x, y;
        x = p[l];
        y = p[r];
        l++;
        r--;
        printf("+ %d %d\n", x, y);
        fflush(stdout);
        int k = 0;
        scanf("%d", &k);
        int a, b;
        a = l;
        b = r;
        int res = r + 1;
        for (; a <= b;)
        {
            int mid = (a + b) / 2;
            if (cmp(k, p[mid]))
            {
                res = mid;
                b = mid - 1;
            }
            else
            {
                a = mid + 1;
            }
        }
        insert(res, k);
    }
    printf("!\n");
    fflush(stdout);
    return 0;
}
```

---

## 作者：SFlyer (赞：0)

先说一个错误的做法。

很容易想到，第一次一定要先排一个序，否则比较难搞。排完序我们首尾配对一直到中间，配成 $\frac{len}{2}$ 个数（原先 $len$ 个数），再排序，重复这个过程。

为什么是错的呢？考虑一个例子：$n=4,r=10,a=\{-10,5,6,9\}$。这样 $|5+6|>r=10$，所以不行。

但是我们发现如果只是首尾配对，不配对其他的，一定是可行的。因为：如果都是正数，很显然；如果一个复一个整，加起来一定不超过绝对值的最大值。我们配对以后直接二分插入的位置就可以了。

关于排序有一个 stl 的技巧：`stable_sort(id+1,id+1+n,cmp);`，其中 `cmp` 函数中询问。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 1e3+3;

int n,id[N],id2[N];

bool ask(int x,int y){
	cout<<"? "<<x<<" "<<y<<endl;
	cout.flush();
	bool f;
	cin>>f;
	return f;
}

bool cmp(int x,int y){
	return ask(x,y);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>n;
	for (int i=1; i<=n; i++){
		id[i]=i;
	}
	stable_sort(id+1,id+1+n,cmp);
	while (n>1){
		cout<<"+ "<<id[1]<<" "<<id[n]<<endl;
		cout.flush();
		int x;
		cin>>x;
		int l=1,r=n;
		while (l+1<r){
			int mid=l+r>>1;
			if (ask(x,id[mid])){
				r=mid;
			}
			else{
				l=mid;
			}
		}
		for (int i=2; i<=l; i++){
			id2[i-1]=id[i];
		}
		id2[l]=x;
		for (int i=l+1; i<=n-1; i++){
			id2[i]=id[i];
		}
		for (int i=1; i<=n; i++){
			id[i]=id2[i];
		}
		n--;
	}
	cout<<"!"<<endl;
	cout.flush();
	return 0;
}
```

---

## 作者：Exp10re (赞：0)

有趣交互题。

## 解题思路

注意到对数列进行排序的操作次数是 $O(n\log n)$ 级别的。

考虑以下做法：先进行排序，每次取最大最小值相加，将和加入数列直到数列仅有一个数为止。

操作次数是 $O(2n\log n + n)$ 的，显然可以通过。

- 最大最小值相加 $\leq R$ 的正确性证明：
  - 记最大最小值分别为 $m_1,m_2$，所有数的和为 $S$。
  - 若 $m_1,m_2$ 不同正负，其和绝对值一定比两者绝对值较大的一个的绝对值要小，即 $|m_1+m_2|\leq \max(|m_1|,|m_2|)$，又因为 $|m_1|,|m_2|\leq m$，所以 $|m_1+m_2|\leq m$ 成立得证。
  - 若 $m_1,m_2$ 同正负，则显然 $S$ 与 $m_1,m_2$ 也同正负。记 $k=S-m_1-m_2$，易得 $|k|=|S|-|m_1+m_2|$，则有 $|k|\leq R$。又因为 $|S|\leq R$，所以 $|S|-|k|\leq R$，即 $|m_1+m_2|\leq m$ 成立，得证。
  
## 代码

值得注意的是，Atcoder 上使用 `printf+fflush(stdout)` 很容易因为未知原因挂掉。建议使用 `cout+endl`。

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MAXN=1010;
long long a[MAXN],n,l[MAXN],lcnt,r[MAXN],rcnt,m;
bool cmp(long long ta,long long tb)
{
	long long ans;
	cout<<"? "<<ta<<" "<<tb<<endl;
//	printf("? %lld %lld\n",ta,tb);
//	fflush(stdout);
	scanf("%lld",&ans);
	if(ans==-1)
	{
		exit(0);
		return false;
	}
	if(ans==1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void del()
{
	long long i,j;
	for(i=1;i<=n-2;i++)
	{
		a[i]=a[i+1];
	}
	a[n]=a[n-1]=0;
	n-=2;
	return;
}
long long merge(long long ta,long long tb)
{
	long long ans;
	cout<<"+ "<<ta<<" "<<tb<<endl;
//	printf("+ %lld %lld\n",ta,tb);
//	fflush(stdout);
	scanf("%lld",&ans);
	del();
	if(ans==-1)
	{
		exit(0);
		return -1;
	}
	return ans;
}
void inc(long long x)
{
	long long l=1,r=n,mid,ans=n+1;
	while(l<=r)
	{
		mid=(l+r)/2;
		if(cmp(x,a[mid]))
		{
			ans=mid;
			r=mid-1;
		}
		else
		{
			l=mid+1;
		}
	}
	long long i;
	for(i=n;i>=ans;i--)
	{
		a[i+1]=a[i];
	}
	a[ans]=x;
	n++;
	return;
}
int main()
{
	long long i;
	scanf("%lld",&m);
	for(i=1;i<=m;i++)
	{
		inc(i);
	}
	while(n>=2)
	{
		inc(merge(a[1],a[n]));
	}
	cout<<"!"<<endl;
//	printf("!");
//	fflush(stdout);
	return 0;
}
```

---

## 作者：fire_and_sweets (赞：0)

这是一道很有意思的交互题。

一上来我的思路是这样的：每次处理 $n$ 个数的时候，就把他从小到大排序，然后一个指针从头到尾，一个指针从尾到头，把他们加起来。

但是却得到了 WA。

仔细分析一下原因：其实有一个明显更优的方法，每一次把和放进去的时候，就重新进行一次排序。这样，我们就可以用堆维护操作了。

但是还是得到了 WA，原因是操作数量过多。

然后我就看了一下 Solution，发现了问题所在：因为我维护了两个堆，所以有两倍的常数，这对操作的步数也有影响。于是，我们考虑利用二分，对每一个读入进来的数做插入排序。插入时可以用 `lower_bound` 优化。

于是便通过了本题。

```
#include <bits/stdc++.h>
using namespace std;

map<pair<int, int>, bool> mp;

bool cmp(const int& _1, const int& _2)
{
	if (mp.count({_1, _2})) return mp[{_1, _2}];
	cout << "? " << _1 << " " << _2 << endl;
	int x;
	cin >> x;
	mp[{_1, _2}] = x;
	mp[{_2, _1}] = x ^ 1;
	return x;
} 
int query(int a, int b)
{
	cout << "+ " << a << " " << b << endl;
	int P;
	cin >> P;
	return P;
} 

deque<int> q;

int main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i ++ ) q.push_back(i);
	sort(q.begin(), q.end(), cmp);
	while (q.size() >= 2)
	{
		int x = q.front();
		int y = q.back();
		q.pop_front(); q.pop_back();
		int mid = query(x, y);
		q.insert(lower_bound(q.begin(), q.end(), mid, cmp), mid);
	}
	cout << "!" << endl;
	return 0;
}
```

---

