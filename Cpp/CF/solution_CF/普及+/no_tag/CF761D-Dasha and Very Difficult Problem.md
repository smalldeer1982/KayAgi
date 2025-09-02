# Dasha and Very Difficult Problem

## 题目描述

# 题目大意
	现有a[i]，b[i]两个数组(l<=a[i]<=b[i]<=r),我们定义p,c两个数组,其中c[i]=b[i]-a[i],p数组是c数组的相对大小,现给你a和p数组,把任意满足的一组b数组求出来.如果没有满足的,则输出‘-1’(没有引号).

## 样例 #1

### 输入

```
5 1 5
1 1 1 1 1
3 1 5 4 2
```

### 输出

```
3 1 5 4 2 ```

## 样例 #2

### 输入

```
4 2 9
3 4 8 9
3 2 1 4
```

### 输出

```
2 2 2 9 ```

## 样例 #3

### 输入

```
6 1 5
1 1 1 1 1 1
2 3 5 4 1 6
```

### 输出

```
-1
```

# 题解

## 作者：QWQ_123 (赞：1)

考虑贪心。

将 $p,a$ 按照 $p$ 从大到小排序。

然后对于最大的那个一定用 $r$ 去减。

然后每次我们设上一次的 $b - a$ 是 $la$，那么我们可以使 $\le a_i + la - 1$ 的数为 $b_i$，使得 $b_i - a_i < la$，那么若 $a_i + la - 1 < l$ 则一定无解，否则就看 $\le a_i + la - 1$ 的数在 $[l,r]$ 内最大满足的是哪一个即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, l, r;
array<int, 3> a[100010];
int b[100010];

int main() {
	scanf("%d%d%d", &n, &l, &r);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i][0]);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i][1]), a[i][2] = i;
	sort(a + 1, a + 1 + n, [&](array<int, 3> a, array<int, 3> b) {
		return a[1] > b[1];
	});

	int la = 0;

	for (int i = 1; i <= n; ++i) {
		if (i == 1) {
			b[a[i][2]] = r;
			la = r - a[i][0];
		} else {
			int t = a[i][0] + la - 1;
			if (t < l) {
				puts("-1");
				return 0;
			}
			t = min(t, r);
			la = t - a[i][0];
			b[a[i][2]] = t;
		}
	}

	for (int i = 1; i <= n; ++i) printf("%d ", b[i]);

	return 0;
}
```

---

## 作者：lpx666666 (赞：0)

## 题面
给定两个数 $l$ 和 $r$ 和两个长度为 $n$ 的数组 $a$ 和 $p$ ，还有两个未知数组分别为 $b$ 和 $c$，并且 $l \le a_i \le b_i \le r$，而 $c_i = b_i - a_i$，$p_i$ 表示在 $c$ 数组中从小到大排序，$c_i$ 在其中的位置，求符合以上条件的 $b$ 数组。

## 思路
可以建一个结构体将所有数组绑定在一起，以 $p_i$ 从小到大排序，那么这一项肯定 $c_i >  c_{i-1}$，我们可以先设 $b_1 = l$，此时 $b_1$ 就一定是最小的，那么下一位就是 $b_i=a_i+c_{i+1}+1$，所以以此类推，最后还原再输出似乎就可以了，于是我得出了以下代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int a,b,p,id;
}arr[10001];
int n,l,r;
bool cmpp(node x,node y){
	return x.id<y.id;
}
bool cmp(node x,node y){
	return x.p<y.p;
}

int main(){
	cin>>n>>l>>r;
	for(int i=1;i<=n;i++){
		cin>>arr[i].a;
		arr[i].id=i;
	}
	for(int i=1;i<=n;i++){
		cin>>arr[i].p;
	}
	sort(arr+1,arr+1+n,cmp);
	arr[1].b=l;
	for(int i=2;i<=n;i++){
		arr[i].b=arr[i].a+arr[i-1].b-arr[i-1].a+1;
		if(arr[i].b>r){
			cout<<-1;
			return 0;
		}
	}
	sort(arr+1,arr+1+n,cmpp);
	for(int i=1;i<=n;i++){
		cout<<arr[i].b<<" ";
	}
	return 0;
}
```
错了，因为我忽略了一个很重要的东西，$l \le b_i$，那么我们无法确定 $b_i$ 怎么办呢？其实我们可以利用等量代换得出 $l \le a_i+c_i$ 即可得出 $c_i \ge l-a_i$ 而 $l-a_i$ 就是 $c_i$ 向下的临界值，那我们就可以判断这个临界值，这一位的临界值如果比上一位的还小，那 $c_i=c_{i-1}+1$，否则就为他的临界值。

最后一点，数组不要只开到 $10^5$，~~你猜我怎么知道的~~。

## 代码
最终功夫不负有心人，调了一中午终于调好了。
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int a,b,p,id,lj;
}arr[1000005];
int n,l,r;
bool cmpp(node x,node y){
	return x.id<y.id;
}
bool cmp(node x,node y){
	return x.p<y.p;
}

int main(){
	cin>>n>>l>>r;
	for(int i=1;i<=n;i++){
		cin>>arr[i].a;
		arr[i].id=i;
	}
	for(int i=1;i<=n;i++){
		cin>>arr[i].p;
	}
	sort(arr+1,arr+1+n,cmp);
	arr[1].b=l;
	arr[1].lj=l-arr[1].a;
	for(int i=2;i<=n;i++){
		if(arr[i-1].lj<l-arr[i].a){
			arr[i].b=l;
			arr[i].lj=l-arr[i].a;
		}
		else{
			arr[i].b=arr[i-1].lj+1+arr[i].a;
			arr[i].lj=arr[i-1].lj+1;
		}
		if(arr[i].b>r){
			cout<<-1;
			return 0;
		}
	}
	sort(arr+1,arr+1+n,cmpp);
	for(int i=1;i<=n;i++){
		cout<<arr[i].b<<" ";
	}
	return 0;
}

```

---

## 作者：Zaku (赞：0)

这是一个构造题，大概橙~黄难度。

#### 解题思路：
用结构体存储数组 $a$，数组 $b$，数组 $p$，数组 $c$，先以数组 $p$ 排序（题目所给的 $p_i$ 实际上是 $c_i$ 之间的大小关系： $p_i=1$ 是最小的， $p_i=2$ 则是第二小 …… $p_i=n$ 则是最大的。)

于是 $c$ 序列应尽可能小，这样可以让 $b$ 数组尽可能小。所以令 $c_i=c_{i-1}+1$，而 $b_1=l$，后面的元素根据题目给的公式来推，若推出来的 $b$ 元素小于 $l$，则将其改为 $l$，$c$ 数组也相应地改变，此后的 $c$ 数组仍按 $c_i=c_{i-1}+1$ 递增；若大于 $r$，由于 $b$ 数组已尽可能小了，不可能构造出符合要求的数组，无解。若有解，再根据原来顺序排序，输出数组。

#### 饱满多汁的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
struct node{
    int a,b,p,c;//四个数组的元素 
    int id;//原来数组元素的顺序，用于还原 
}A[N];
bool cmp(node x,node y);//第一次排序，按p数组得到c数组的位置 
bool cmq(node x,node y);//第二次排序，还原各元素位置 
int main(){
	int n,l,r;cin>>n>>l>>r;
    for(int i=1;i<=n;i++){
        scanf("%d",&A[i].a);
        A[i].id=i;//保存原顺序，便于还原 
    }
    for(int i=1;i<=n;i++)scanf("%d",&A[i].p);
    sort(A+1,A+1+n,cmp);
    A[1].b=l;//由于第一个b元素应尽可能小，故设为l 
    A[1].c=l-A[1].a; 
    for(int i=2;i<=n;i++){
        A[i].c=A[i-1].c+1;
        A[i].b=A[i].a+A[i].c;
        if(A[i].b<l) A[i].b=l,A[i].c=l-A[i].a;//如果b<l，改为l；c也相应的改变 
        if(A[i].b>r){//如果b>r，因为不可能再小了，直接输出-1 
        	cout<<-1<<endl;
        	return 0;
		}
    }
    sort(A+1,A+1+n,cmq);//还原数组 
    for(int i=1;i<=n;i++)
        printf("%d ",A[i].b);
    return 0;
}
bool cmp(node x,node y){return x.p<y.p;}
bool cmq(node x,node y){return x.id<y.id;}
```


---

## 作者：dead_X (赞：0)

## 思路
我们先将所有的数按照 $p$ 排序。

然后你发现这时你需要让 $b_i-a_i$ 单调递增。

注意到前面的 $b_i-a_i$ 更小是更优的。所以你每次只需要取最小的 $b_i$ 就好了。

这玩意有 $2$ 个条件，一个是 $b_i\in[l,r]$ ，另一个是 $b_i-a_i>b_{i-1}-a_{i-1}$ 。
## 代码
```
#include<bits/stdc++.h>
#define int long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
using namespace std;
pair<int,int> a[1000003];
int ans[1000003];
int id[1000003];
signed main()
{
    int n=read(),l=read(),r=read();
    for(int i=1; i<=n; i++) a[i].second=read();
    for(int i=1; i<=n; i++) a[i].first=read(),id[a[i].first]=i;
    sort(a+1,a+n+1);
    ans[id[a[1].first]]=l;
    int lst=l-a[1].second+1;
    for(int i=2; i<=n; i++) 
    {
        ans[id[a[i].first]]=max(l,lst+a[i].second);
        if(ans[id[a[i].first]]>r) puts("-1"),exit(0);
        lst=max(lst,ans[id[a[i].first]]-a[i].second)+1;
    }
    for(int i=1; i<=n; i++) printf("%lld ",ans[i]);
    return 0;
}
```

---

## 作者：ggtmjts (赞：0)

	这道题目用到的是构造和贪心。
	因为c[i]=b[i]-a[i],但是c数组有一定的顺序，
	先排序，之后就是贪心，c越小b也越小，就更加的优
	若这里看不懂就去看代码吧！！！！！！
	code：
	var n,i,l,r,t,x,o:longint;
	a,b,c:array[0..300000]of longint;
	begin
	readln(n,l,r);
	for I:=1 to n do read(a[i]);
	for I:=1 to n do
	  begin
	  read(x);
	  b[x]:=i;     //用到的是计数排序
	  end;
	t:=-maxlongint;  
	for i:=1 to n do
	  begin     //l-a[b[i]]就是假设b是l，这样c就越小
 	  if l-a[b[i]]>t then o:=l-a[b[i]]
	  else o:=t+1;//如果比上一次大，保存现在的，否则是上次的+1
	  if o+a[b[i]]>r then  //超范围了        //因为c有顺序
	    begin 
	    write(-1);
	    halt;
	    end;
	  t:=o;c[b[i]]:=t;   //保存求出的c数组，并记录这次的值
	  end;           //求出b
	for i:=1 to n do write(c[i]+a[i] ,' ');
	end.

---

