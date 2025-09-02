# [USACO07DEC] Bookshelf B

## 题目描述

Farmer John 最近为奶牛们的图书馆添置了一个巨大的书架，尽管它是如此的大，但它还是几乎瞬间就被各种各样的书塞满了。现在，只有书架的顶上还留有一点空间。

所有 $N(1 \le N \le 20,000)$ 头奶牛都有一个确定的身高 $H_i(1 \le H_i \le 10,000)$。设所有奶牛身高的和为 $S$。书架的高度为 $B$，并且保证 $1 \le B \le S < 2,000,000,007$。

为了够到比最高的那头奶牛还要高的书架顶，奶牛们不得不像演杂技一般，一头站在另一头的背上，叠成一座“奶牛塔”。当然，这个塔的高度，就是塔中所有奶牛的身高之和。为了往书架顶上放东西，所有奶牛的身高和必须不小于书架的高度。

显然，塔中的奶牛数目越多，整座塔就越不稳定，于是奶牛们希望在能够到书架顶的前提下，让塔中奶牛的数目尽量少。现在，奶牛们找到了你，希望你帮她们计算这个最小的数目。

## 说明/提示

输入说明：

一共有 $6$ 头奶牛，书架的高度为 $40$，奶牛们的身高在 $6\dots19$ 之间。


输出说明：

一种只用 $3$ 头奶牛就达到高度 $40$ 的方法：$18+11+13$。当然还有其他方法，在此不一一列出了。

## 样例 #1

### 输入

```
6 40
6
18
11
13
19
11```

### 输出

```
3```

# 题解

## 作者：Victorique_De_Blois (赞：371)

- 虽然您可以用快排过，但是您不会手打堆。

- 虽然您可以用基数过，但是您不会手打堆。

- 虽然您可以用STL打堆排，但是您还是不会手打堆。

- 显而易见，手打堆是可行且最能练习我们代码质量的，因为稍有不慎就会错。

- 以上全部都是扯淡。

这里讲解一下**堆排**

### 什么是堆

堆（英语：heap)是计算机科学中一类特殊的数据结构的统称。堆通常是一个可以被看做一棵树的数组对象。

### 堆的定义

- 堆中某个节点的值总是**不大于或不小于其父节点的值**；

- 堆总是一棵**完全二叉树**。

### 堆的分类

分**大根堆**和**小根堆**

例如：

								1
                               / \
                              2   8
                             /\   /\
                            3  7 8  9 
这是一个小根堆。小根堆的定义是：任何一个子节点都不小于它的父节点。因此，堆的根节点总是最小。

又例如：

								9
                               / \
                              6   8
                             /\   /\
                            3  2 1  4 		
这是一个大根堆。大根堆的定义是：任何一个子节点都不大于它的父节点。因此，堆的根节点总是最大。
                                                	
### 堆的存储与遍历。

堆用数组存储。

拿上面的小根堆举例

								1
                               / \
                              2   8
                             /\   /\
                            3  7 8  9 
用数组存储就是：

| 1 | 2 | 3 | 4 | 5 | 6 | 7 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 1 | 2 | 8 | 3 | 7 | 8 | 9 | 

显然，堆的存储是按照每一层的顺序存进数组里的。

那么，怎么找到一个堆的父亲与儿子？

拿第二个点2举例。

如图，第二个点2的父亲是第一个点1，第二个点2的儿子为第四个点3与第五个点7。

得出结论：一个点的父亲为这个点的数组下表整除2;一个点的儿子为这个点的数组下标乘2或乘2加1.

很好理解吧。

### 堆的操作。

重点是如何维护一个堆。

在运行代码的时候，经常会从堆里面插入元素或取出元素。

因此堆的秩序经常会被打乱。

维护堆需要掌握两个操作：将一个点上浮或下沉。

这里拿小根堆举例，大根堆也是一样的。

#### 下沉操作：


这里我将点一更改成9

								9
                               / \
                              2   8
                             /\   /\
                            3  7 8  9 
                        
| 1 | 2 | 3 | 4 | 5 | 6 | 7 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 9 | 2 | 8 | 3 | 7 | 8 | 9 | 

它已经不是一个正常的堆了，至少不是一个正常的小根堆。

这时候我们就要将它下沉。

下沉关键代码：

    void down(int x)//x为需要下沉的点的下标
    {
        while((a[x]>=a[x*2]&&x*2<=n)||(a[x]>=a[2*x+1]&&x*2+1<=n))//只要找到有一个点小于它，那么就下沉，直无法下沉为止。。
        {
            if(a[x*2]<=a[x*2+1])//两个子节点，往更小的地方下沉。
            {
                swap(a[x],a[x*2]);
                x*=2;//需要改变下标。
            }
            else
            {
                swap(a[x],a[x*2+1]);
                x=2*x+1;
            }
        }
    }
    
下沉之后它就成了这样：

								2
                               / \
                              3   8
                             /\   /\
                            9  7 8  9
                         
| 1 | 2 | 3 | 4 | 5 | 6 | 7 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 2 | 3 | 8 | 9 | 7 | 8 | 9 | 

符合堆的性质。

#### 上浮操作：

比下沉简单多了，不作太多讲解。

拿小根堆举例，当一个节点的父节点比它大，那么它就上浮until它呆在它应有的位置为止。

上浮代码：

    void up(int x)
    {
        while(a[x]<a[x/2]&&x>1)//注意这个x>1。如果没了它可能会使x变成0。
        {
            swap(a[x],a[x/2]);
            x/=2;
        }
    }

#### 插入操作

往堆里面插入一个元素，可能会使堆不正常。

那么这样做，（不分大小根堆）：

1.最大下标加1，一个元素插入堆底（数组后）。

2.对它实行上升操作。

上代码可能会好理解一点。

    void work(int x)
    {
        a[++n]=x;
        up(n);
    }
    
#### 建堆操作

好吧重点来了。

这里讲的建堆，就是给你很多数字，把它存进数组里使其变成一个堆。

注意，排序一遍之后再建堆也是可以的，但是你既然排序过了还用什么堆排呢？

很简单。

1.最大标加1，插入队尾。

2.上升。

3.回到1.，直到没有数据再次插入。

#### 删除堆顶元素

很多人不知道为什么要删除。

其实当这个堆是一个正常的堆时，它的根节点总是最大或最小的。

堆排序只要求你把它输出出来，然后将根的值赋为堆底元素（即当前最大下标所指的数组，记得最大下标要减一），最后对堆顶（因为执行上一操作会打破堆的正常秩序）执行下沉操作。

给出代码：

    	a[1] =a[n];
        n--;
        down(1);
        
其中a数组是存储这个堆的数组，n为它的最大下标。

## 就到这里了吧。

回到原题，这一题要求我们每次累加最大的。

我们就建大根堆。

具体注释代码会有的。

有些地方会编译错误，说不定是故意的。

	#include<cstdio>
    #include<iostream>
    #define N 1000000
    using namespace std;
    int a[N],n;//a数组存储堆，n为堆的最大下标。
    void down(int x)//下沉
    {
        while((a[x]<=a[x*2]&&x*2<=n)||(a[x]<=a[2*x+1]&&x*2+1<=n))
        {
            int wrong=0;
            try{//检查异常情况
                if(a[x*2]>=a[x*2+1]) throw wrong;//当找出x的左儿子比x的右二子大（或相等）时停止try的运行并抛出异常。
                swap(a[x],a[x*2+1]);
                x=2*x+1;
            }
            catch(int error){//当接收到异常
                if(wrong == error)
                {
                    swap(a[x],a[x*2]);
                    x*=2;
                }
            }
            //实际上这个try和throw和catch完全可以用if和else 和else if 代替，但是如此写比较正式（扯淡吧）
        }
    }
    void up(int x)//下沉
    {
        while(a[x]>a[x/2]&&x>1)
        {
            swap(a[x],a[x/2]);
            x/=2;
        }
    }
    void work(int x)//插入堆底
    {
        a[++n]=x;
        up(n);
    }
    int main()
    {
        int ans=0,sum=0,h;
        int nn;
        scanf("%d%d",&nn,&h)//nn代表要插入的元素数量，h代表书架的高度。
        int b;
        for(register int i=1;i<=nn;i++)
        {
            scanf("%d",&b);
            work(b);//读入一个插入一个建堆。
        }
        while(true)
        {
            int wrong = 0;
            sum+=a[1];//大根堆，堆顶最大。
            ans++;
            try{	
			if(sum>=h) throw wrong;//当高度足够时跳出。
			a[1] =a[n];
			n--;
			down(1);
		}
		catch(int error)
		{
			if(wrong==error)
				break;
		}
	}
	printf("%d",ans);
	return 0;
 } 
 
~~啊，累死我了的说~~

---

## 作者：chenpengda (赞：112)

### 其实这道题不用堆

快排特欢乐

最后一个判断其实可以用while

上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int high[20005];
bool cmp(int a,int b)//使用sort排序定义从大到小
{
	return a>b;
}
int main()
{
	int n,b;
	cin>>n>>b;
	for(int i=0;i<n;i++)
	{
		cin>>high[i];
	}
	sort(high,high+n,cmp);//sort一键排序
	int sum=0,ans=0;
	while(sum<b)//只要高度不够就继续叠
	{
		sum+=high[ans];
		ans++;
	}
	cout<<ans;
	return 0;
}
```

思想是贪心：

$\color{red} \text{每一次用最高的奶牛来叠}$

所以用sort

其中定义了一个函数cmp，意义就是从大到小排序(默认从小到大）

看到很多人最后判断的时候用for

我只能说

$\color{blue} \text{你们能给while一点合理的（人）代码权吗？}$

---

## 作者：Brave_Cattle (赞：76)

这道题可以用Splay来做
将所有的奶牛的身高加入splay中,从第n小的身高开始查询,并每次给需要的总高度减去第n小的身高,并且计数器++.
因为splay可以直接维护第k小的值,所以代码实现上没什么问题.
下面上代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=20000+5;

int n, lim;
int cnt = 0;
int ans = 0;
int root = 0;

struct node{
  int fa, ch[2], cnt, size, val;
}t[N];

bool get(int x){
  return t[t[x].fa].ch[1] == x;
}

void up(int x){
  t[x].size = t[t[x].ch[0]].size + t[t[x].ch[1]].size + t[x].cnt;
}

void rotate(int x){
  int fa = t[x].fa , gfa = t[fa].fa;
  int d1 = get(x) , d2 = get(fa);
  t[fa].ch[d1]=t[x].ch[d1^1]; t[t[x].ch[d1^1]].fa=fa;
  t[x].ch[d1^1] = fa , t[fa].fa = x;
  t[gfa].ch[d2] = x , t[x].fa = gfa;
  up(fa); up(x);
}

void splay(int x,int goal){
  while(t[x].fa != goal){
    int fa = t[x].fa , gfa = t[fa].fa;
    int d1 = get(x) , d2 = get(fa);
    if(gfa != goal){
      if(d1 == d2) rotate(fa);
      else rotate(x);
    }
    rotate(x);
  }
  if(goal == 0) root = x;
}

void insert(int val){
  int node = root , fa = 0;
  while(node && t[node].val != val)
    fa = node , node = t[node].ch[t[node].val<val];
  if(node) t[node].cnt++;
  else{
    node = ++cnt;
    if(fa) t[fa].ch[t[fa].val<val] = node;
    t[node].fa = fa;
    t[node].val = val;
    t[node].cnt = 1;
    t[node].size = 1;
  }
  splay(node , 0);
}

int find(int x){
  int node = root;
  while(t[node].val!=x && t[node].ch[t[node].val<x])
    node = t[node].ch[t[node].val<x];
  return node;
}

int pre(int x,int kind){
  splay(find(x) , 0);
  int node = root;
  if(t[node].val < x && kind == 0) return node;
  if(t[node].val > x && kind == 1) return node;
  node = t[node].ch[kind];
  while(t[node].ch[kind^1])
    node = t[node].ch[kind^1];
  return node;
}

void delet(int x){
  int last = pre(x,0) , next = pre(x,1);
  splay(last , 0); splay(next , last);
  int node = t[next].ch[0];
  if(t[node].cnt > 1) t[node].cnt--;
  else t[next].ch[0] = 0;
}

int kth(int k){
  int node = root;
  while(1){
    int son = t[node].ch[0];
    if(k <= t[son].size) node = son;
    else if(k > t[son].size+t[node].cnt){
      k -= t[son].size + t[node].cnt;
      node = t[node].ch[1];
    }
    else return t[node].val;
  }
}

int main(){
  int x; cin >> n >> lim;
  for(int i=1;i<=n;i++)
    cin >> x , insert(x);
  while(lim>0){
    x = kth(n);
    lim -= x;
    delet(x);
    n--; ans++;
  }
  cout << ans << endl;
  return 0;
}
```

---

## 作者：HFColin (赞：47)

题意简单来说，就是在一串数中取最少的数，使取的数和大于等于给定数。

这道题是贪心，先选最大的数（即最高的奶牛），一定能使取的数的数目（即奶牛数）最小

如下是证明：

在序列a\_1,a\_2,……a\_n（a\_1>=a\_2>=a\_3……>=a\_n）中

若有k个数a\_i1,a\_i2,a\_i3,a\_i4……a\_ik（i1>i2>i3……>ik,且i1,i2……ik为1～n之间的整数) a\_i1+……+a\_ik>=h

因为i1>i2>i3……>ik,且i1,i2……ik为1～n之间的整数

所以 i1>=1 i2>=2 …… ik>=k

所以 a\_i1<=a\_1 a\_i2<=a\_2 …… a\_ik<=a\_k

则 a\_1+……+a\_k>=a\_i1+……+a\_ik>=h

所以 先选最大的数（即最高的奶牛），一定能使取的数的数目（即奶牛数）最小

那我们下一步就是排序了

在这里我介绍几种较快的做法

```cpp
    #include<cstdio>
    #include<queue>
    using namespace std;
    int t[10001];
    int main()
    {
        int n,h,hi,i,ans=0;
        scanf("%d %d",&n,&h);
        for (i=0;i<n;i++)
            scanf("%d",&hi),t[hi]++;
        for (i=10000;h>0;i--)
        {
            if (i*t[i]<=h) h-=i*t[i],ans+=t[i];
            else ans+=h/i+1,h=0;
        }
        printf("%d",ans);
        return 0;
    }
```
桶排，由于数据规模小，这里可以用桶排。
```cpp
    #include<cstdio>
    #include<algorithm>
    using namespace std;
    int w[20000];
    int main()
    {
        int n,h,i;
        scanf("%d %d",&n,&h);
        for (i=0;i<n;i++) scanf("%d",&w[i]);
        sort(w,w+n);
        for (i=n-1;h>0;i--) h-=w[i];
        printf("%d",n-i-1);
        return 0;
    }
```
快排，用的是模板快排，注意这里默认是从小到大排序
```cpp
    #include<cstdio>
    #include<queue>
    using namespace std;
    priority_queue <int> que;
    int main()
    {
        int n,h,i,hi;
        scanf("%d %d",&n,&h);
        for (i=0;i<n;i++)
            scanf("%d",&hi),que.push(hi);
        for (i=0;h>0;i++)
        {
            h-=que.top();
            que.pop();
        }
        printf("%d",i);
        return 0;
    }
堆排，这里用的是STL的优先队列，默认大根堆，在需要数较小时比快排快
```

---

## 作者：孑丿孓 (赞：17)

#  超级书架

##  很水的一个题，输入数据，再用sort进行排序，在倒着按照最大的进行累加，超过书架就行了。
### 选择牛的高度肯定要按最高的牛来进行选择，所以进行排序后，在倒着计算就行。
话不多说了
附上AC代码：




```
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
ll a[20005];
int main(){
    int n , k = 0;     //n表述牛的数量，k代表需要几头牛
    ll b , sum = 0;   //b代表书架高度，sum代表牛加起来的高度
    cin >> n >> b;
    for(int i = 1 ; i <= n ;i++){
        cin >> a[i];   // 输入牛的身高
    }
    sort(a + 1,a + n + 1);  //进行排序
    for(int j = n ; j >= 1 ; j--){
        if(sum > b){  //判断几头牛的身高加起来是否超过书架的高度
            break;
        }
        else sum += a[j];
        k++;    //需要几头牛
    }
    cout << k << endl;
    return 0;
}

```




---

## 作者：Or_Black (赞：7)

其实这题没那么难，挺好理解的，只要先建一个数组，用来存奶牛的高度。再从大到小排序一下：

```c

------------

#include<iostream>

using namespace std;

int main()
{
    int n,src[20005];//定义奶牛数量
    long long bookshelf;//定义书架的高度 
   	cin>>n>>bookshelf; 
    //从大到小排序
    for(int i=0;i<n;i++)
		cin>>src[i]; 
    for(int i = 0; i < n; i++)
    {
        for(int j = i+1; j < n; j++)
        {
            if(src[i]<src[j])    //如果前一个元素小于后一个元素
            {
                int temp;        //临时变量
                temp = src[i];
                src[i] = src[j]; //大的元素到前一个位置
                src[j] = temp;   //小的元素到后一个位置
            }
        }
    }_
```
然后一直取出数组中最大的数加到奶牛的身高计数器height中再与书架高度作对比，用一个ans来记载奶牛数量就OK了```c


------------
	int height=0,ans=0; //定义奶牛塔的高度 
   	for(int i=0;height<bookshelf;i++)
	{
   		height=height+src[i];
   		ans++;
	} 
	cout<<ans<<endl;
    return 0;
}
```


---

## 作者：添哥 (赞：6)

# 本萌新第一次发题解
我挑了一题比较水的题目，~~虽然我还是用了好长时间才做出来~~，进来一看，发现各位大佬们貌似都不是用数组做的，赶紧来抢个位置啊！！

------------
## 分析
因为要求奶牛数量尽量少，所以每次都要选最高的奶牛，我们可以用贪心算法。

------------

## 附上C++满分代码：
```c
#include<iostream>
using namespace std;
int main()
{
    long long n,b,max,max2,sum=0,a=0;//免得它数据溢出。。。
    cin>>n>>b;
    long long h[n];
    for(int i=1;i<=n;i++)
    {
        cin>>h[i];//按要求输入
    }
    while(sum<b)
    {
        a++;//奶牛只数+1
        max=0;//初始化一下
        for(int i=1;i<=n;i++)
        {
            if(h[i]>max)//如果这只奶牛身高大于当前最高奶牛的身高
            {
                max=h[i];//记录奶牛的身高
                max2=i;//记录奶牛编号
            }
        }
        sum+=max;
        h[max2]=0;//把这只奶牛的身高设为0（因为我不晓得怎么删除元素）
    }
    cout<<a;//输出答案
    return 0;//完美收尾。
}
```
~~~~打字好累啊~~~~，点个赞吧。

---

## 作者：AubRain (赞：6)

c++12行代码！已ac

```cpp
#include<bits/stdc++.h>       //c++万能头文件 
int h[100000];      //数组要大一点，否则会RE 
using namespace std;
bool cmp(int a,int b){return a>b;}    //定义函数用来降序排列 
int main(){
    int n,i;
    long long H,s=0;      //最好定义成long long型，防止数据过大 
    cin>>n>>H;
    for(int k=0;k<n;k++) cin>>h[k];
    sort(h,h+n,cmp);       //直接降序排列 
    for( i=0;s<H;i++)s+=h[i];      //s为i+1头牛的总高度 ，超过H时跳出循环 
    cout<<i;        //输出几头牛 
}
```

---

## 作者：Nightriver (赞：6)

这道题目应该按从大到小排序的，

但若用冒泡会超时，

所以用快排。

```cpp
var
  n,i,j,k,t,s,r:longint;
  a:array[1..100051]of longint;
procedure qsort(l,r:longint);//快排过程（这个就不讲了）
var
  i,j,k,t:longint;
begin
  i:=l;
  j:=r;
  k:=a[(i+r) div 2];
  repeat
    while a[i]>k do inc(i);//注意！要从大到小
    while a[j]<k do dec(j);
    if i<=j then begin
      t:=a[i];
      a[i]:=a[j];
      a[j]:=t;
      inc(i);
      dec(j);
    end;
  until i>j;
  if l<j then qsort(l,j);
  if i<r then qsort(i,r);
end;
begin//主程序
  read(n,r);
  for i:=1 to n do read(a[i]);
  qsort(1,n);//快排
  s:=0;
  k:=0;
  for i:=1 to n do begin
    if k>=r then begin
      s:=i-1;
      break;//追求速度，就不继续执行循环了
    end
    else k:=k+a[i];
    if (i=n)and(k<r) then s:=-1;
  end;
  writeln(s);/输出
end.//结束程序
```

---

## 作者：CT_Res (赞：5)

#### 在这个除了$C++$就是$Pascal$的地方

### python了解一下

- 本题的贪心思路很明了——每次选高的奶牛


1. 对奶牛身高排序
2. 选取最高者，用书架高减去之
3. 当书架高$<=0$时,输出选取的次数，否则重复2

下面贴代码

```python
a=[];ans=0 #初始化
#输入
n,h=map(int,input().split(' '))
for x in range(n):
    a.append(int(input()))
a.sort() # 排序
x=n-1
while h>0: #书架高>0,即还需要奶牛
    h=h-a[x] #减去当前最高的奶牛
    ans=ans+1 #计数器+1
    x=x-1 #下一头奶牛
print (ans) #输出
```

---

## 作者：『　』 (赞：5)

本题可以用c++自带stl中的优先队列（就是堆）秒

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>//优先队列需加的头文件
#define For(i,a,b)  for(i=a;i<=b;i++)//宏定义，将for换成这个东西
#define Forr(i,a,b)  for(i=a;i>=b;i--)
using namespace std;
int n;
int main()
{
    priority_queue<int>qq;//定义int型队列qq
    int ans=0,m=0,k,i,j,t;
    scanf("%d%d",&n,&k);
    For(i,1,n)
    {
        scanf("%d",&t);
        qq.push(t);//将t压入优先队列qq
    }
    t=0;
    while(m<=k)
    {
        m+=qq.top();//取出队首最大数,累和高度
        qq.pop();//弹出队首
        t++;//计数
    }
    printf("%d\n",t);//输出
    return 0;
}
```

---

## 作者：Sinwind (赞：4)

------------

# 分析

**奶牛的身高尽量选最大的，奶牛的头数才最少**，需要将奶牛的身高从大到小排序。

------------

# 思路

0. 注意：**大型数组要开在main函数外，成为全局变量**，若开在main函数中，就是开在栈区里，有可能超过栈区的大小；

1. 用**桶排序**，循环num（奶牛的总数）次，读入每头奶牛的身高height，对应的桶bucket[height]++；

2. 从后往前遍历bucket中的每一个元素。

- 若bucket[i]==0，跳过本次循环；

- 若bucket[i]!=0，循环（**可能有多头奶牛身高相同**）：
	- 若满足条件sum >=shelf，输出奶牛的头数count，结束程序；
    - 若不满足条件：奶牛的总身高sum每次加上当前奶牛的身高i；因为该奶牛的身高已经计算过一次，bucket[i]--；记录数量，奶牛的头数count++。

------------

# 代码

```cpp
#include <iostream>

using namespace std;

int num;    			//奶牛的总数
int count = 0;          //需要的奶牛的最少数量
int height; 			//奶牛的身高
int sum = 0;    		//奶牛的总身高
int shelf;          	//书架高度
int bucket[10001]={0};  //桶排序

int main(void)
{
	cin >> num >> shelf;
	
	while(num--)
	{
		cin >> height;
		
		bucket[height]++;
	}
	
	for(int i = 10000; i >= 1; i--)
	{
		while(bucket[i])
		{
			if(sum >= shelf)
			{
				cout << count;
				return 0;
			}
			
			sum += i;
			bucket[i]--;
			count++;
		}
	}
}
```

---

## 作者：Meditator (赞：2)

刚刚翻着红题，发现了这道题目，心中窃喜~~：又被我找到一道水题！~~

不到五分钟，我就写好代码，交了上去。

代码如下。

```cpp
#include<iostream>
#include<algorithm>//头文件（最好不要用万能头，因为有2MB的内存）
using namespace std;
bool cmp(int x,int y);//让sort从大到小排序（默认是从小到大）
long long i,m,n,h[10001],sum;//各种变量
int main()
{
	cin>>n>>m;
	for (i=1;i<=n;i++)
	  cin>>h[i];//输入n，m和奶牛身高
	sort(h+1,h+n+1,cmp);//从大到小排序
	for (i=1;i<=n;i++)
	{
		sum+=h[i];//累加奶牛身高
		if (sum>=m)
		{
			cout<<i<<endl;
			break;
		}//一旦奶牛总身高超过了书架高度，就跳出循环，输出奶牛数量i
	}
	return 0;//好习惯
}
bool cmp(int x,int y)
{
	return x>y;
}
```
然后，结果出来了……[R28868080](https://www.luogu.com.cn/record/28868080)

竟然RE了！我又仔细地看了一遍题目，哦，1<=n<=20000。~~（我们老师说我们是虾(瞎)的传人，还真没错）~~

AC代码！[R28868168](https://www.luogu.com.cn/record/28868168)

```cpp
#include<iostream>
#include<algorithm>//头文件（最好不要用万能头，因为有2MB的内存）
using namespace std;
bool cmp(int x,int y);//让sort从大到小排序（默认是从小到大）
long long i,m,n,h[20001],sum;//各种变量
int main()
{
	cin>>n>>m;
	for (i=1;i<=n;i++)
	  cin>>h[i];//输入n，m和奶牛身高
	sort(h+1,h+n+1,cmp);//从大到小排序
	for (i=1;i<=n;i++)
	{
		sum+=h[i];//累加奶牛身高
		if (sum>=m)
		{
			cout<<i<<endl;
			break;
		}//一旦奶牛总身高超过了书架高度，就跳出循环，输出奶牛数量i
	}
	return 0;//好习惯
}
bool cmp(int x,int y)
{
	return x>y;
}
```

---

## 作者：Acos_x (赞：2)

# 题目链接
[点击此处](https://www.luogu.org/problem/P2676)

# 思路
首先我们知道，如果想要塔中奶牛数目尽量少，每只奶牛的身高就必须尽量更高。

又因为题目中给出，为了往书架顶上放东西，所有奶牛的身高和必须不小于书架的高度。

所以，奶牛塔总高度并不一定必须正好到达书架顶部，只需比书架高度更高，东西即可放到书架顶部。

那么，我们就可以对奶牛的身高进行排序，并从身高最高的奶牛处开始选择，将奶牛加入奶牛塔。

每当有一只奶牛加入奶牛塔，奶牛数目增加1。

当奶牛塔总高度大于等于书架高度时，当前奶牛塔奶牛数即为答案。

# 代码
这里使用了冒泡排序算法进行排序。

冒泡排序就是将序列中的元素两两比较，小的在前，这样就可以得到有序序列。

在此不详细解释，可自己查询相关资料。

```cpp
#include<iostream>
using namespace std;
int main()
{
    int N,B; //N是奶牛总数，B是书架高度
    cin>>N>>B;
    int H[N],temp,count = 0; //H是存储全部奶牛身高的数组
    for (int i = 0;i <N;i++) 
    {
        cin>>H[i]; // 导入奶牛身高
    }
    for(int i = N-1;i>=1;i--) //冒泡排序
    for(int j = 0;j<i;j++)
        if(H[j]>H[j+1]) 
            {
                temp = H[j];
                H[j] = H[j+1];
                H[j+1] = temp;

            }
        temp = 0;
        for(int i = N-1;i != 0;i--) //开始叠奶牛塔
        {
            temp += H[i];
            count += 1;
            if (temp >= B) //奶牛塔高度大于书架高度，奶牛塔完成
            {
                cout<<count<<endl; //输出答案
                return 0; //这里return 0可以直接结束程序
            }
        }
}
    
```



---

## 作者：Dusker (赞：2)

题目描述

Farmer John最近为奶牛们的图书馆添置了一个巨大的书架，尽管它是如此的大，但它还是几乎瞬间就被各种各样的书塞满了。现在，只有书架的顶上还留有一点空间。 所有N(1 <= N <= 20,000)头奶牛都有一个确定的身高H\_i(1 <= H\_i <= 10,000)。设所有奶牛身高的和为S。书架的高度为B，并且保证 1 <= B <= S < 2,000,000,007。 为了够到比最高的那头奶牛还要高的书架顶，奶牛们不得不象演杂技一般，一头站在另一头的背上，叠成一座“奶牛塔”。当然，这个塔的高度，就是塔中所有奶牛的身高之和。为了往书架顶上放东西，所有奶牛的身高和必须不小于书架的高度。显然，塔中的奶牛数目越多，整座塔就越不稳定，于是奶牛们希望在能够到书架顶的前提下，让塔中奶牛的数目尽量少。 现在，奶牛们找到了你，希望你帮她们计算这个最小的数目。

输入输出格式

输入格式：

第1行: 2个用空格隔开的整数：N 和 B \* 第2..N+1行: 第i+1行是1个整数：H\_i

输出格式：

第1行: 输出1个整数，即最少要多少头奶牛叠成塔，才能够到书架顶部


思路：从题面分析可得，每次需要找最高的一头奶牛，当“奶牛塔”的高度>=书架高度时即为答案。因为该题局部最优解就是全局最优解，并且有后无效性，所以该题直接sort+贪心+模拟就可以。

...cpp
```cpp
#include<bits/stdc++.h> //万能头文件
#define mmax 100000 //奶牛个数在0到10005之间，直接开大一点到100000
using namespace std;
long long n,b,a[mmax],ans,cnt; //因为奶牛的高度在0到2,000,000,007之间，int会爆炸，所以用long long
int main()
{
    scanf("%lld%lld",&n,&b);  //读入
    for(int i=1;i<=n;i++)
      scanf("%lld",&a[i]); //读入
    sort(a+1,a+n+1,greater<long long>()); //sort快排，虽然不稳定但是方便233，greater<long long>()是从大到小排序
    for(int i=1;i<=n;i++)
      {
          cnt+=a[i]; //贪心开始，每次让最高的奶牛上奶牛塔
          ans++; //奶牛数+1
          if(cnt>=b) //如果奶牛塔高度>=书架高度，停止循环，不让其他奶牛上奶牛塔
          break; //停止循环
      }
    printf("%lld",ans); //输出答案
    return 0;
}
```

---

## 作者：「QQ红包」 (赞：2)

方法很简单，首先先排序，然后就贪心，优先让高的人上。

并不知道楼下为何手写快排……不会从大到小排序？

```cpp

#include<set>  
#include<map>  
#include<list>  
#include<queue>  
#include<stack>  
#include<string>  
#include<math.h>  
#include<time.h>  
#include<vector>  
#include<bitset>  
#include<memory>  
#include<utility>  
#include<stdio.h>  
#include<sstream>  
#include<iostream>  
#include<stdlib.h>  
#include<string.h>  
#include<algorithm> 
#define LL unsigned long long   
long long n,s,sum,i;//long long防炸  书架高度为s; 
int a[20010];
int cmp(const int &a,const int &b) //从大到小排序 
{  
    if(a>b) return 1;  
        else return 0;  
}  
using namespace std;
int main()
{
    scanf("%d %d",&n,&s);
    for (i=1;i<=n;i++)
        scanf("%d",&a[i]);//用cin cout会浪费不必要的时间
    sort(a+1,a+n+1,cmp);//从大到小排序 
    sum=0;i=0;
    while (sum<s)
    {
        i++;
        sum+=a[i];
    } 
    cout<<i;
    return 0;
}

```

---

## 作者：我没有小白 (赞：2)

可以说，这是一道灰常好（shui）的贪心模板题（沙比提）
首先，题目中给的s貌似没有什么用处，其次，题目中有一堆情景题设（feihua），我可以大概的概括一下题意
	
    		一堆奶女要叠起来去够到书架上的空间，至少需要多少奶女？
看，多么的清晰，就是从大到小排一下序而已，然后加和判断，完事。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n , high[40000] , ans , b;
bool cmp(int x,int y)
{
	return x>y;
}//cmp函数设定条件 
int main()
{
	cin >> n >> b;
	for (int i = 1; i <= n; i ++)
		cin >> high[i];
	sort(high+1,high+1+n,cmp);//从大到小排序求最少奶女 
	for (int i = 1; i <= n; i ++)
	{
		ans+=high[i];//加和 
		if(ans>b)//如果可以够得到 
		{
			cout << i;//i喂当前到多少个奶女了 
			return 0;//直接退出程序 
		}
	}
}
```
管理大大求过，小妹好辛苦的

---

## 作者：LMB_001 (赞：2)

小弟不才，Pascal转c++刚一个星期，请大家指教。这道题不难，把数组排一个序，然后for循环统计就行了，特献上Pascal和c++代码各一份，不喜勿喷哦

Pascal：


```cpp
var
 a:array[1..20000]of longint;
 n,i,b,s,k:longint;
procedure sort(l,r: longint);
      var
         i,j,x,y: longint;
      begin
         i:=l;
         j:=r;
         x:=a[(l+r) div 2];
         repeat
           while a[i]>x do
            inc(i);
           while x>a[j] do
            dec(j);
           if not(i>j) then
             begin
                y:=a[i];
                a[i]:=a[j];
                a[j]:=y;
                inc(i);
                j:=j-1;
             end;
         until i>j;
         if l<j then
           sort(l,j);
         if i<r then
           sort(i,r);
      end;//嘿嘿，调用的快排
begin
 readln(n,b);
 for i:=1 to n do readln(a[i]);//读入
 sort(1,n);k:=0;s:=0;//快排
 for i:=1 to n do begin
  s:=s+a[i];//奶牛塔的高度
  inc(k);//用的奶牛数量
  if s>=b then break;//如果奶牛塔比这个书架高或相等，就弹出
 end;
 writeln(k);//输出用的奶牛数量
end.
```
c++：
```cpp
#include <bits/stdc++.h>//万能头文件
using namespace std;
int a[20000];
bool cmp(int x,int y){
    return(x>y); 
```
}//为了从大到小
```cpp
int main(){
    int n,i,b,s=0;
    cin>>n>>b;
    for (i=0;i<n;i++) cin>>a[i];//读入
    sort(a,a+n,cmp);//快排
    for (i=0;i<n;i++){
        s=s+a[i];//奶牛塔高度
        if (s>=b) {cout<<i+1;return 0;}//如果奶牛塔比书架高或相等，就输出i+1！因为我用的数组从0开始的！
    }
    return 0;
}
看懂再抄哦，不然还是不懂哦，一起向神犇加油吧
```

---

## 作者：yyy2015c01 (赞：2)

贪心
```cpp

#include<set>
#include<map>
#include<list>
#include<queue>
#include<stack>
#include<string>
#include<math.h>
#include<time.h>
#include<vector>
#include<bitset>
#include<memory>
#include<utility>
#include<stdio.h>
#include<sstream>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
#define LL long long
LL n,s,sum,i;
int a[20010];
int cmp(const int &a,const int &b)
{
    return a>b;
}
using namespace std;
int main()
{
    scanf("%d %d",&n,&s);
    for (i=1; i<=n; i++)
        scanf("%d",&a[i]);
    sort(a+1,a+n+1,cmp);
    sum=0;
    i=0;
    while (sum<s)
        sum+=a[++i];
    printf("%d",i);
    return 0;
}

```

---

## 作者：Meicout (赞：1)

###第一次发题解，不好的地方请见谅。


###这题其实不难，核心思想就是一个排序，以满足即把高的奶牛先放上去。


###看到没有C++的桶排序，所以来一发。


###我们注意到题目中奶牛的身高的范围是 H\_i (1 <= H\_i <= 10,000) ，最高只有10000，所以空间绝对够，而且时间复杂性为 O(n)，而快排至少也要 O(n log n)。


###不多解释了，下面附上代码。


```cpp
#include<iostream>
const int maxn = 100010;            //数组开大一点，反正也不会炸。blabla (但是不能只开一万多，至于为什么自己去想)
using namespace std;
int cow[maxn],cow1[maxn];            
//看到了吗？我们的桶也是用maxn来定义最大值的，万一相同大小的个数超过了一万怎么办 ↑↑↑ 
int main() {
    int n,hig,maxm=0,ans=0,num=0;
    cin>>n>>hig;
    for(int i = 1; i <= n; i++) {
        cin>>cow[i];
        cow1[cow[i]]++;                //将等于cow[i]的值全部装入第cow[i]桶中
        if(cow[i]>maxm)
            maxm=cow[i];        //更新最大值 
    }
    for(int i = maxm; i >= 1; i--) {        //从大往小加，因为题目要求的是最少的奶牛头数 
        if(cow1[i]!=0)
            for(int j = 1; j <= cow1[i]; j++) {            //相同的整数，要重复加 
                ans+=i;
                num++;
                if(ans>=hig) {            //如果已经超过了书架高度，输出头数 ，退出程序 
                    cout<<num;
                    return 0;
                }
            }
    }
}
```

---

## 作者：LQHqwq (赞：1)

因为题目要求奶牛的数量要尽量少，所以我们可以在每次叠奶牛塔时找剩下的牛中

最高的一头，代码如下：



```cpp
{----------------------------------------------------}
var
  n, i, t, k, w: Longint;
  a, f: array[1..100000] of Longint;
procedure kp(low, high: Longint);        //先把奶牛身高排个序
var
  i, j, t: Longint;
  mid: Real;
begin
  i := low;
  j := high;
  mid := a[(low + high) div 2];
  while i < j do
  begin
    while a[i] < mid do
      i := i + 1;
    while a[j] > mid do
      j := j - 1;
    if i <= j then
    begin
      t := a[i];
      a[i] := a[j];
      a[j] := t;
      i := i + 1;
      j := j - 1;
    end;
  end;
  if i < high then
    kp(i, high);
  if low < j then
    kp(low, j);
end;
begin
        readln(n, k);
        for i := 1 to n do
                readln(a[i]);
        kp(1, n);
        for i := n downto 1 do                //从最高的奶牛开始叠
        begin
                inc(w);                       //已取出的奶牛数
                f[w] := a[i];                 //将奶牛们放进一个数组保存
        end;
        while k > 0 do                        //开始叠奶牛塔！！(场景一定很壮观A...A)
        begin
                t := t + 1;                   //叠奶牛塔的奶牛数
                k := k - f[t];                //离书架顶还有多远
        end;
        Write(t);                             //输出最小数目
end.
```

---

## 作者：wawcac (赞：1)

这题数据较水，我用选择排序也全AC了

```cpp
#include<stdio.h>
int main()
{
    long long int n,b,a[50000]={0},i,s=0,num=0,max,maxi;
    scanf("%lld%lld",&n,&b);
    for(i=0;i<n;i++)
        scanf("%lld",&a[i]);//输入数据
    while(s<b)//奶牛总高度小于书架高度时，接着叠牛塔
    {
        for(i=0,max=maxi=-1;i<n;i++)
        {
            if(a[i]>max) {max=a[i];maxi=i;}
```
}//遍历一遍，找出当前最高的奶牛

```cpp
        s+=max;//叠到牛塔上
        num++;//牛的只数增加一
        a[maxi]=a[n];
        a[n]=0;
        n--;//把选过的甩到数组最后，并减少当前只数
    }
    printf("%lld",num);//输出牛塔上有几只牛
    return 0;
}
建议大家用快排，不然遇到很坑的数据就TLE了
```

---

## 作者：guobaipeng0 (赞：1)

```cpp
var n,b,s,i,j,temp:longint;
  a:array[1..20000] of longint;
procedure qsort(l,r:longint);            //这一段都是快排
var i,j,x,y:longint;
begin
  i:=l;j:=r;x:=a[(l+r) div 2];             //x取中间值
  repeat
    while a[i]>x do inc(i);
    //搜索，如果这个数比中间值小的话就继续，直到找到比中间值大的数
    while x>a[j] do dec(j);
   //和上面相反，如果这个数比中间值大就继续，直到找到比中间值小的数
    if i<=j then
    begin
      //这里交换，条件是大的数在数列的左边，小的在数列右边才行
      y:=a[i];a[i]:=a[j];a[j]:=y;
      inc(i); dec(j);     //继续搜索，没有这一行和下一行会死循环，永不停止
    end;
  until i>j;
  if l<j then qsort(l,j);
   //这里和下一行都是判断，如果还有一段没有搜索过，就搜索那一段
  if i<r then qsort(i,r);
end;
begin
  readln(n,b);   //输入
  for i:=1 to n do readln(a[i]);   //输入奶牛的身高
  qsort(1,n);   //快速排序大到小
  for i:=1 to n do   //贪心
  begin
    s:=s+a[i];    //建造奶牛塔
    if s>=b then begin writeln(i); break; end;  //如果够高，就停止了，输出了
  end;
end.
```

---

## 作者：AmuroRay (赞：1)

方法很简单：首先快排，再模拟。

C语言程序如下：

        
```cpp
# include<stdio.h>
# include<stdlib.h>
int a[100000];
void qsort (int l,int r)//快排
{
    int i,j,w,c;
    i=l;
    j=r;
    w=a[(l+r)/2];
    do{
        while(a[i]>w)i++;
        while(a[j]<w)j--;
        if(i<=j)
        {
            c=a[i];
            a[i]=a[j];
            a[j]=c;
            i++;
            j--;
        }
    }while(i<=j);
    if(j>l)qsort(l,j);
    if(i<r)qsort(i,r);
}
int main(){
    int n,i,sum=0,b;
    scanf("%d%d",&n,&b);
    for(i=1;i<=n;i++)
    scanf("%d",&a[i]);
    qsort(1,n);
    i=1;
    while(sum<b)//当身高和大于书架高度输出牛数
    {
        sum+=a[i];
        i++;
    }
    printf("%d\n",i-1);
}
```

---

## 作者：ArnoD (赞：1)

水题，思路很简单，从大到小排序，再用一个while循环做到奶牛塔高度大于等于书架高度，输出奶牛数就行了。

下面贴代码：

```delphi

var
  n,m,i,s:longint;
  a:array[1..20000] of longint; 
procedure qsort(l,r:longint);
var
  i,j,m,t:longint;
begin
  i:=l;
  j:=r;
  m:=a[(i+j) div 2];
  repeat
    while a[i]>m do
      inc(i);
    while a[j]<m do
      dec(j);
    if i<=j then
    begin
      t:=a[i];
      a[i]:=a[j];
      a[j]:=t;
      inc(i);
      dec(j);
    end;
  until i>j;
  if i<r then
    qsort(i,r);
  if j>l then
    qsort(l,j);
end;
begin
  readln(n,m);
  for i:=1 to n do
    readln(a[i]);
  qsort(1,n);//排序
  s:=0;
  i:=0;
  while s<m do//贪心
  begin
    inc(i);
    s:=s+a[i];
  end;
  writeln(i);
end.

```

---

## 作者：飞翔 (赞：1)

巨水贪心。按照奶牛的高度排序，再依次从高往低累加，加到书架高度就停下来，输出加了多少个数即可。

代码：

```delphi
var
  a:array[1..20000]of longint;
  i,n,b,sum,ans:longint;
procedure qsort(l,r:longint);
var
  i,j,temp,mid:longint;
begin
  i:=l; j:=r;
  mid:=a[(l+r) div 2];
  repeat
    while a[i]<mid do inc(i);
    while a[j]>mid do dec(j);
    if i<=j then
    begin
      temp:=a[i];a[i]:=a[j];a[j]:=temp;
      inc(i);dec(j);
    end;
  until i>j;
  if l<j then qsort(l,j);
  if i<r then qsort(i,r);
end;
begin
  readln(n,b);
  for i:=1 to n do readln(a[i]);
  qsort(1,n);
  sum:=0;ans:=0;
  for i:=n downto 1 do
  begin
    if sum>=b then break;
    sum:=sum+a[i];
    inc(ans);
  end;
  write(ans);
end.
```

---

## 作者：yizixuan_Kitty (赞：1)

	#include<bits/stdc++.h> //万能头文件
	#define mmax 100000 //奶牛个数在0到10005之间，直接开大一点到100000
	using namespace std;
	long long n,b,a[mmax],ans,cnt; //因为奶牛的高度在0到2,000,000,007之间，int会爆炸，所以用long long
	int main()
	{
    	scanf("%lld%lld",&n,&b);  //读入
    	for(int i=1;i<=n;i++)
      	scanf("%lld",&a[i]); //读入
    	sort(a+1,a+n+1,greater<long long>()); //sort快排，虽然不稳定但是方便233，greater<long long>()是从大到小排序
    	for(int i=1;i<=n;i++)
      	{
          	cnt+=a[i]; //贪心开始，每次让最高的奶牛上奶牛塔
          	ans++; //奶牛数+1
          	if(cnt>=b) //如果奶牛塔高度>=书架高度，停止循环，不让其他奶牛上奶牛塔
          	break; //停止循环
      	}
    	printf("%lld",ans); //输出答案
    return 0;
	}

---

## 作者：Kuchinashi (赞：1)

本人初二蒟蒻，看到楼下一堆大犇的恐怖解法%%%，来讲一讲自己的简单思路。

首先初看此题，第一个想法就是排序。从大到小排，再一个个加过去比较，就可以得到最少答案，然后AC了。

看代码吧。

```cpp
#include<bits/stdc++.h>  //万能头文件
using namespace std;
int a[20001];  //用于存储奶牛高度
int n, b;
int main()
{
    scanf("%d%d", &n, &b);
    int tmp=0, ans=1;  //tmp用于存放当前垒起来的奶牛高度，因为不会出现书架高度为0的情况，所以ans=1
    for(int i=1;i<=n;i++)
        scanf("%d", &a[i]);
    sort(a+1,a+n+1);  //用C++的std标准库的函数排序，表示从a[1]开始，排到a[n]，具体使用方法可以自己去查资料
    for(int i=n;i>=1;i--)
    {
        tmp += a[i];  //累加奶牛高度
        if(tmp>=b)  //判断奶牛高度是否合格
            {
                printf("%d", ans);  //如果合格，直接输出答案，并结束程序
                return 0;
            }
        else ans++;
    }
    return 0;
}
```
因为题面并没有说有无解的情况，所以就这样啦~


---

## 作者：_ljx_ (赞：1)

C++：贪心

```cpp
#include<iostream>
using namespace std;
int main()
{
    int p,o,i,l=0,z=0,u=0;
    cin>>p>>o;//一个记录奶牛头数，一个记录塔高度    
    int a[p],b=20001;    
    for(i=0;i<p;i++)    
    {    
         cin>>a[i];//输入    
     }
     while(u<o)//到值超过塔高时，退出    
    {  
         for(i=0;i<p;i++)//依次找值最大的
         {
             if(a[i]==z) z=z;//如果有相同的，z的值不变    
             else if(a[i]>z && a[i]<b) z=a[i];        
         }    
    u+=z;//再累加最大        
    b=z;       
    l++;//累计奶牛头数
   }
   cout<<l;//输出奶牛头数    
   return 0;//hh!简单吧！
} 

```

---

## 作者：骗分过样例 (赞：0)

这道题思路简洁明了：

~~开挂。~~

其实没必要。开O2也有好处。

开始说正话：

本题需要最少的牛来达到书架高度，只要排序，然后就是个漂亮的贪心。本题压根不用01背包和DP

[AC记录](https://www.luogu.org/record/22849198)（防伪标识）

下面是你们想要的，附带详解：

```cpp
#include<bits/stdc++.h> //刷题专用
using namespace std; //别忘加
bool cmp(long long a,long long b); //比较函数 
int main(){
	vector<long long> cow; //储存高度，骚写法 
	long long h; //书架高度
	long long n; //奶牛个数
	long long total=0; //储存高度
	long long ctotal=0; //储存牛的数量 
	cin>>n>>h; //输入 
	for(long long i=0;i<n;i++){
		long long tmp;
		cin>>tmp; //输入 
		cow.push_back(tmp); //压入容器 
	}
	sort(cow.begin(),cow.end(),cmp); //排序 
	for(long long i=0;i<n;i++){
		if(total+cow.at(i)>=h){ //如果加上就达标 
			ctotal++; //牛数加一 
			break; //跳出 
		}
		else{ //否则 
			total+=cow.at(i); //加上此牛的高度
			ctotal++; //牛数加一 
		} 
	}
	cout<<ctotal; //输出！！ 
	return 0; //完美结束 
}
bool cmp(long long a,long long b){
	return a>b; //返回大的 
}
```


---

## 作者：远辰 (赞：0)

蒟蒻开始了复习，从贪心开始了。

这道题目很经典，如果不了解贪心的思想，你也有可能做出来；


------------

对于书架高度m，让奶牛可以够到，而且奶牛数量足够少，利用贪心思想，由局部最优解推到整个最优解，为了让奶牛尽量少，则在选择时，可以对身高排序，从尾到头扫，每次累加sum，如果sum>=m,则跳出循环，记录当前i，ans=n-i+1；

这道题相当于每次选择最大的，然后将最大的删去，一次次循环，对于每次的选择，如果你选择一个比当前状态小的，可知大的比小的对于答案贡献更大些，若选择小的，可能造成之后奶牛的数量比最优解多(废话)则选当前状态最大的；


------------

代码！！！
```cpp
#include<bits/stdc++.h>
#define re register
typedef long long ll;
const int maxn=2e4+10;
using namespace std;
ll h[maxn],n,m,sum=0,ans;
 /*h[]表示高度，n是奶牛数量，m是书架高度,sum用来记录，ans表示奶牛数量 即最终结果*/ 
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    scanf("%lld%lld",&n,&m);
	for(re int i=1;i<=n;i++){
		scanf("%lld",&h[i]);
	}
	sort(h+1,h+1+n); //将身高排序 
	for(re int i=n;i>=1;i--){     //从最高的开始贪心，累加高度，当sum>=m时跳出循环，ans即为结果 
		sum+=h[i]; 
		if(sum>=m){
			ans=n-i+1;
			break;
		}
	}
	printf("%lld",ans);	
	return 0;
}
```




---

## 作者：zjl543 (赞：0)



这道题好简单~

其实，也不简单。

用贪心做就可以了（虽然我自己都不知道什么是贪心）

比一比即可

我可是只用了~~不到1年的时间~~ _（废话）_ 就AC了！

以下是代码（我用的是c++11):

```
#include<iostream>//多余的头文件，可以不加
#include<bits/stdc++.h>//万能的头文件
using namespace std;//cin/cout的必备内容
long long s,t;//定义部分
long long n,m,a[20001];//还是定义部分
bool cmp(int x,int y)//sort的附件
{
	return x>y;//从大到小排序
}
int main()//主函数
{
	cin>>n>>m;//输入部分，不说了
	for(int i=1;i<=n;i++)//还是输入
	{
		cin>>a[i];//输入输入
	}
	sort(a+1,a+1+n,cmp);//sort是STL中的排序函数
	for(int i=1;i<=n;i++)//判断部分
	{
		if(t<m)//如果不够高
		{
			s++;//还需一头奶牛
			t+=a[i];//将仅次于的奶牛扔到塔顶，好好呆着，别动，动了就摔死你！
		}
	}
	cout<<s;//输出需要的奶牛
	return 0;//再见了，迥长的代码！
}

/*
此非最优解
可以改进哦
*/

```

没有最好，只有更好，大家可以在我的基础上继续优化哦！

/*

(这里是题外话）

	这是本蒟蒻第一次发题解，希望管理员大大给过！

*/

（请您不要**直接**抄题解哦！)

好了，今天的题解就到这里了

---

## 作者：梁博文314 (赞：0)

这个题还是比较好的，适合入门组选手

下面是来自一个蒟蒻的比较好懂的题解

最好是用桶排序来解决，毕竟是一个比较简单的排序方法
```cpp
#include<iostream>
using namespace std;
int main()
{
	int n,b;
	int maxn=0;
	int h1[200010];//根据数据范围制定数组盛放身高，但是我写着写着觉得没什么用
	int h2[200010]={};//桶排序所用的桶
	int sum=0;//中间身高和
	int ans=0;//结果，也就是奶牛数量
	cin>>n>>b;
	for(int i=1;i<=n;i++)
	{
		cin>>h1[i];
		h2[h1[i]]++;//桶排序
		if(h1[i]>=maxn)
		{
			maxn=h1[i];//求出最大值
		}
	}
	for(int i=maxn;i>=0;i--)//从最大开始判断
	{
		for(int j=1;j<=h2[i];j++)
		{
			sum=sum+i;
			ans++;//能进这个小循环都是有这个数的
			if(sum>=b)
		    {
			    break;//判断是不是到顶了，同时，这个break是跳出里面这个循环
		    }
		}
		if(sum>=b)
		{
			break;//跳出大循环
		}
	}
	cout<<ans;
}
```

---

## 作者：fmt931200363 (赞：0)

其实不必要多复杂，就只要****暴力+暴力****

~~~~字符串、贪心、排序之类的~~~~去死吧！！！！！！！

不废话了，上满分题解！

------------
```
#include<bits/stdc++.h>	//万能头文件
using namespace std;
int main(){
	int n,s,ans=0,x1;	//n只羊，楼高s，ans是最终羊数，x1是替换的；
	int x[20001];		//羊之身高。
    cin>>n>>s;			//羊与楼；
    for(int i=0;i<n;i++){
        cin>>x[i];		//输入身高；
    }
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){	//强换！！！！！！管什么贪心!!!!!!!!
            if(x[i]<x[j]){
                x1=x[i];
				x[i]=x[j];
                x[j]=x1;
            }
        }
    }
    for(int i=0;i<n;i++){	//求羊数
		if(x[i]<=s){
			ans++;
			s-=x[i];
		}
		else{
			ans++;
			break;
		}
    }
    cout<<ans<<endl;	//输出
    return 0;
}
```

---

## 作者：JAMES1Harden3 (赞：0)

蒟蒻第一次发题解，先附上代码，一步一步的分析
```cpp
include<iostream>
include<cstdio>
include<algorithm>//用sort要用这个库
using namespace std;
int a[20001];
int main()
{ int n,s=0,b,ans=0;//s是当前奶牛塔的高度，ans是当前塔内的奶牛数目
cin>>n>>b;
int x=n;
for(int i=1;i<=n;i++)
{ 
	scanf("%d",&a[i]);
} 
sort(a+1,a+n+1);//STL排序，因为要求奶牛数目的最小值，所以要从最高的奶牛开始排
while(s<b)//只要还没够到书架顶，就再叠上一只奶牛 
{ 
	s=s+a[x];//总高度加上新叠上的奶牛高度
	x--;//更新当前不在塔内的最高奶牛的编号
	ans++;//更新当前奶牛塔内的奶牛数目 
}
cout<<ans;//输出最小的奶牛数目
return 0;//完美结束
}
```

---

## 作者：empty (赞：0)

# 归并

翻了一遍题解，居然没有用归并的。

普及一下，快排虽好，可快排是一种不稳定且有悲剧情况的排序。归并的时间复杂度为（nlongn），速度快，稳定。

归并也有它好的地方，当然也有不好的地方。

不过母庸置疑的是,快排更深入人心。


```cpp
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#define ll long long
using namespace std;
int nnt[100100],r[100100];
void GB(int s,int t)
{
 if(s==t) return;- 
 int mid=(s+t)/2;
 GB(s,mid);
 GB(mid+1,t);
 int i=s,j=mid+1,k=s;
 while((i<=mid)&&(j<=t))
  {
   if(nnt[i]<=nnt[j])
   {
    r[k]=nnt[i];k++;i++;
   }
   else
   {
    r[k]=nnt[j];k++;j++;
   }
  }
 while(i<=mid)
 {
  r[k]=nnt[i];k++;i++;
 }
 while(j<=t)
 {
  r[k]=nnt[j];k++;j++;
 }
 for(int i=s;i<=t;i++) nnt[i]=r[i];
}
int main()
{
 ll n,b,s=0,j=0;
 scanf("%lld %lld\n",&n,&b);
 for(int i=1;i<=n;i++) scanf("%d\n",&nnt[i]);
 GB(1,n);
 for(int i=n;i>=1;i--) {s+=nnt[i];j++;if(s>=b) break;}
 printf("%lld",j);
 return 0;
}
```

---

## 作者：Pure_gas (赞：0)

题目描述

Farmer John最近为奶牛们的图书馆添置了一个巨大的书架，尽管它是如此的大，但它还是几乎瞬间就被各种各样的书塞满了。现在，只有书架的顶上还留有一点空间。 所有N(1 <= N <= 20,000)头奶牛都有一个确定的身高H\_i(1 <= H\_i <= 10,000)。设所有奶牛身高的和为S。书架的高度为B，并且保证 1 <= B <= S < 2,000,000,007。 为了够到比最高的那头奶牛还要高的书架顶，奶牛们不得不象演杂技一般，一头站在另一头的背上，叠成一座“奶牛塔”。当然，这个塔的高度，就是塔中所有奶牛的身高之和。为了往书架顶上放东西，所有奶牛的身高和必须不小于书架的高度。显然，塔中的奶牛数目越多，整座塔就越不稳定，于是奶牛们希望在能够到书架顶的前提下，让塔中奶牛的数目尽量少。 现在，奶牛们找到了你，希望你帮她们计算这个最小的数目。


思路：从题面分析可得，每次需要找最高的一头奶牛，当“奶牛塔”的高度>=书架高度时即为答案。因为该题局部最优解就是全局最优解，并且有后无效性，所以该题直接贪心就可以。

pascal




```cpp
var
  n,b,sum,min,i,k:longint;
  a:array[1..10000] of longint;
begin
  readln(n,b);
  for i:=1 to n do//这道题目适合这样排序，因为数据不大，时间复杂度O(n),快排O(n log(n))
    begin
      readln(k);
      inc(a[k]);//身高为k的+1
    end;
  min:=0;//最小数目
  sum:=0;//奶牛身高和
  i:=10000;//从最大找起，反正数据也不大
  while sum<b do //开始叠奶牛塔！！(场景一定很壮观)！！
    if a[i]>0 then begin
                     inc(sum,i);//身高和+i
                     inc(min);//奶牛头数+1
                     dec(a[i]); //身高为i的奶牛的头数-1
                   end
              else dec(i); //没了
  write(min);
end.
```

---

## 作者：Shallowy (赞：0)

时间复杂度最低的当然是桶排（计数排序）了。（O(n)的复杂度，快排最快也就O(nlogn)...）

pascal代码

```cpp
var
  n,b,i,t,ans:longint;
  a:array[0..20000] of longint;  //存高度
  s:array[0..10000] of longint;  //桶，s[i]表示i高度的奶牛有s[i]只
begin
  readln(n,b);
  for i:=1 to n do
    begin
      readln(a[i]);
      inc(s[a[i]]);  //放桶里
    end;
  i:=10000;
  while t<b do  //可以是for i:=10000 downto 1 do
    if s[i]>0 then  //还有
      begin
        inc(t,i);  //累加高度
        inc(ans);  //总数+1
        dec(s[i]);  //出桶
      end
              else
      dec(i);  //没了，继续往下找
  write(ans);
end.
```

---

## 作者：MMINO (赞：0)

快排，然后从高到矮一个一个把身高加起来直到总高度>=B即可。

直接上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int s=0,n,b,h[20001];//定义变量
int main()
{
    cin>>n>>b;
    for(int i=1;i<=n;i++)
        scanf("%d",&h[i]);//输入
    sort(h+1,h+n+1);//快排
    for(int i=n;i>=1;i--)//从高到矮
    {
        s+=h[i];
        if(s>=b)//达到高度
        {
            cout<<n-i+1;//输出奶牛只数
            break;
        } 
    }
    return 0;
}
```

---

## 作者：DWY_me (赞：0)

本题主要思想运用贪心排序（一定要用快排），然后让较高的奶牛依次叠加，直到达到m高度为止（等于也算达到！！！）

----------------------------------------------------------------------------------------------------------------------------------



```cpp
var n,m,i:longint;
s,x:int64;//貌似不需要int64。。。
a:array[0..100001] of int64;//貌似不需要int64。。。
    procedure sort(l,r: longint);
      var
         i,j,x,y: longint;
      begin
         i:=l;
         j:=r;
         x:=a[(l+r) div 2];
         repeat
           while a[i]>x do
            inc(i);
           while x>a[j] do
            dec(j);
           if not(i>j) then
             begin
                y:=a[i];
                a[i]:=a[j];
                a[j]:=y;
                inc(i);
                j:=j-1;
             end;
         until i>j;
         if l<j then
           sort(l,j);
         if i<r then
           sort(i,r);
      end;
begin
readln(n,m);//读入n,m
for i:=1 to n do
  readln(a[i]);//读入每头奶牛高度
sort(1,n);//快排从大到小排序
for i:=1 to n do//从最大到最小累加
  begin
  x:=x+a[i];//高度增加
  s:=s+1;//牛数增加
  if x>=m then break;//发现高度已经到达m时（等于也算），直接退出
  end;
writeln(s);//输出所需奶牛数
end.
```
----------------------------------------------------------------------------------------------------------------------------------
（PS：前两次就是因为没判断等于导致第二个点错误）


---

## 作者：bestcow (赞：0)

大家在这里可以运用快排的方法瞬间通过哦

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long n,b,a[20001]={0},c=0;
int comp(const int & a,const int &b)
{
    return a>b;
}
int main()
{
    scanf("%d%d",&n,&b);
    for(int x=1;x<=n;x++)
    {
        scanf("%d",&a[x]);//记得用scanf读入数据特别快哦
    }
    sort(a+1,a+n+1,comp);//然后快排，从大到小
    for(int x=1;x<=n;x++)
    {
        c=c+a[x];
        if(c>=b)//排完后判断
        {
            cout<<x;
            break;
        }
    }
}
```

---

## 作者：何旭的小粉丝 (赞：0)

C++11。不B，直接滚代码，毕竟题目太水

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;//多一点没事，少一点要你命 
int n,h;//n是奶牛数，h是书架高度 
int main()//直接主程序走起
{
    cin>>n>>h;//读入 。注意这里可以先读数据，再开数组，节约空间 
int a[n],ans=0,sum=0;//a[n]是各只牛牛的身高，ans是计数用的，sum是计算奶牛总高度用的 
    for(int i=1;i<=n;i++)
        cin>>a[i];//读入身高 
    sort(a+1,a+1+n);//从低到高排的。强迫症可以再加一个参数（当然要多写很多东西） 
    for(int i=n;i>=1;i--)//由于懒癌晚期，没加排序条件，这里要从最后的最高的那只开始排 
    {
        sum+=a[i];
        ans++;//注意加了一只马上动计数器 
        if(sum>=h)//够了就炸 
        {
            cout<<ans<<endl;
            return 0;
        }
    }
}
```

---

## 作者：CYR666 (赞：0)

用快排即可，把奶牛的高度从矮到高排序，再从最高的开始，即为最优方案

不多说了，上代码


```cpp
var a:array[1..20000] of longint;
    n,i,k,c,g:longint;
procedure kp(l,r:longint);
var i,j,x,t:longint;
begin
 if l>=r then exit;
 i:=l;j:=r;
 x:=a[(l+r)div 2];
 repeat
  while a[i]<x do inc(i);
  while a[j]>x do dec(j);
  if i<=j then begin
                t:=a[i];
                a[i]:=a[j];
                a[j]:=t;
                inc(i);
                dec(j);
               end;
 until i>j;
 kp(l,j);  
 kp(i,r);
end;                    
begin
 c:=0;     //所使用的奶牛的高度和 
 g:=0;    //所使用的奶牛的个数
 readln(n,k);    //读入
 for i:=1 to n do readln(a[i]);
 kp(1,n);   //快速排序
 for i:=n downto 1 do  //从高到矮
  begin
   c:=c+a[i];  //总高度加上当前奶牛高度
   inc(g);  //使用奶牛个数加一
   if c>=k then break;  //若总高度大于书架，就跳出
  end;
 write(g);  //输出使用奶牛个数
end.
```

---

## 作者：ghj1222 (赞：0)

###之前我发的题解有误，已更改

```cpp
很好的一道练手题~
难道就没有人用pq做么？
n,k不解释
ans是答案
t是输入的tmp
注：k在程序运行过程中是指还需要填充的高度
主要思想：贪心，每次让最高的奶牛上去(因为题目要求希望奶牛数量要少，所以要让更高的上去啊)
//然而我承认我习惯用stl了
```
```cpp
#include <iostream>
#include <queue>
using namespace std;
int n,k,ans=0,t;
priority_queue<int>q;
int main()
{
    cin >> n >> k;
    while(n--)
    {
        cin >> t;
        q.push(t);
    }
    while(k>0)
    {
        k-=q.top();
        q.pop();//我把这句写成q.top()都能ac，不可思议(之前我的题解就是这里有误)
        ans++;
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：何昊燊1046 (赞：0)

```cpp
var n,m,i,j,s1,s,w:longint;    
    a:array[1..100000] of longint;
begin  
  readln(n,m); //输入奶牛的数量和书架的高度；
  for i:=1 to n do readln(a[i]);  //输入所有奶牛的高度；
  for i:=1 to n-1 do   //循环；
    for j:=i+1 to n do     
      if a[i]<a[j] then begin w:=a[i];a[i]:=a[j];a[j]:=w;end;  //把所有奶牛的高度从大到小排序；
  for i:=1 to n do begin s:=s+a[i];inc(s1);if s>=m then break;end;  //累加奶牛的高度，一直到超过书架为止；
  writeln(s1);  //输出至少需要多少头奶牛；
end.
```

---

