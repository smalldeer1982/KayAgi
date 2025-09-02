# Conan and Agasa play a Card Game

## 题目描述

题目简要描述

有 $n$ 张卡牌，第 $i$ 张上写着 $a_i$。Conan 和 Agasa 轮流操作，Conan 先手。每回合中，玩家选择一张卡牌，然后移除它本身和所有点数严格小于它的卡牌。如果玩家需要操作时已经没有卡牌了，他就输了。

假设双方玩家决顶聪明，请判断谁会赢。

## 样例 #1

### 输入

```
3
4 5 7
```

### 输出

```
Conan
```

## 样例 #2

### 输入

```
2
1 1
```

### 输出

```
Agasa
```

# 题解

## 作者：ckk11288 (赞：3)

这道题是典型的**博弈论**。

结论简单且不难推出：

若有一张牌有奇数个，Conan 赢。

否则 Agasa 赢。

**为什么呢？**

如果所有的牌都有偶数个那么后手就可以跟先手拿一样的牌，最后的结果总是先手无牌可拿。

否则先手就可以轻而易举地获胜了。

现在想必代码怎么打已经很清楚明了了。代码能力较弱的同学可以继续看代码部分。

**Code:**
```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,b[114514],minn=1e9,maxn;//利用maxn与minn缩小范围，可以做到更快。
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		b[x]++;//b[x]表示数字为x的牌有b[x]个，桶排序思想
		minn=min(minn,x);
		maxn=max(maxn,x);//计算牌的最大值与最小值
	}
	for(int i=minn;i<=maxn;i++)//列举每个卡牌数字
	{
		if(b[i]%2!=0)//若有任意一张牌有奇数个，那么Conan赢
		{
			puts("Conan");
			exit(0);//同return 0
		}
	}
	puts("Agasa");//否则Agasa赢
    return 0;
}

```

---

## 作者：naroto2022 (赞：2)

这题就是一题简单的博弈论，如果有一张牌的数量为奇数，则 Conan 赢，
否则 Agasa 赢。

~~还记得小学时令人害怕的必胜策略吧~~~ 

因为如果所有的牌的数量都有偶数个，则先手拿什么牌，后手就那什么牌，后手就赢了，否则先手胜

#### 思路：

用一个桶排序来统计每一张牌出现的次数，再用 $minn$ 和 $maxn$ 变量来统计数组最小值与最大值，在两数之间寻找有没有出现次数为奇数的牌（~~我一开始没写，直接乌拉~~）

话不多说，直接上代码！

```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,t[100005],minn=100005,maxn,x;//t是桶排序的数组，来统计每张牌出现的次数，minn求最小数,maxn求最大数（缩小时间，我一开始没写，第2个点直接无了！）。
int main(){
	cin>>n;
	for(int i=1; i<=n; i++){
		cin>>x;
		if(minn>x) minn=x;//统计最小值。
		if(maxn<x) maxn=x;//统计最大值。
		t[x]++;//出现一次就加一次。
	}
	for(int i=minn; i<=maxn; i++)//在最小值与最大值之间搜索有没有牌出现次数为奇数。
		if(t[i]%2!=0){//如果有张牌出现的次数为奇数。
			cout<<"Conan";//则Conan赢了。
			return 0;//程序直接结束。
		}
	cout<<"Agasa";//如果没牌是奇数，则Agasa赢了。
    return 0;//养成好习惯。
}
```
### 洛谷讲究学术诚信，请勿复制！！！

---

## 作者：Super_Builder (赞：1)

一道简单的博弈论。  

## 思路

我们可以先记录每张牌的个数，如果这个牌的个数为奇数，则 Conan 胜利，如果全部为偶数，Agase 胜利。

## 证明

如果说所有牌为偶数，那么无论 Conan 取哪张牌，Agasa 都可以和他取一样的，最终让 Conan 失败。  

如果不满足，那么 Agasa 会无法操作。

## AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int bk[100005],n;
signed main(){
	scanf("%lld",&n);
	for(int i=1,x;i<=n;i++){
		scanf("%lld",&x);
		bk[x]++;
	}
	for(int i=1;i<=100000;i++){
		if(bk[i]%2){
			puts("Conan");
			return 0;
		}
	}
	puts("Agasa");
	return 0;
}
```

~~话说 Agase 真的是绝顶聪明的玩家吗？~~

---

## 作者：kevin1616 (赞：1)

### 审题
有 $n$ 张卡牌，第 $i$ 张上写着 $a_i$。Conan 和 Agasa 轮流操作，Conan 先手。每回合中，玩家选择一张卡牌，然后移除它本身和所有点数严格小于它的卡牌。如果玩家需要操作时已经没有卡牌了，他就输了。判断最后谁会赢。
***
### 方法
【博弈论】这种题一般是找规律或者计算。
***
### 思路
如果所有的牌都有偶数个，那么 Agasa 就可以跟 Conan 拿一样的牌，最后的结果总是 Conan 无牌可拿。

如果有任意一组牌有奇数个，Conan 就可以拿最大的奇数个的牌，就可以获胜了。

所以我们可以依据这个性质，遇见一个奇数个的牌堆就是 Conan 赢，最后还没跳出程序就是 Agasa 赢。
***
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[100005];
int main(){
	cin >> n;
	for(int i = 1;i <= n;i++){
		int x;
		cin >> x;
		a[x]++; //统计这个牌所在的牌堆
	}
	for(int i = 1;i <= 100000;i++){
	    if(a[i] % 2 == 1){ //遇见一个奇数牌堆
	        cout << "Conan";
	        return 0;
	    }
	}
	cout << "Agasa"; //全都是偶数牌堆
	return 0;
} 
```
不抄题解，从我做起！

---

## 作者：wangyi_c (赞：1)

## 0.前言

[题目传送门](https://www.luogu.com.cn/problem/CF914B)

## 1.题目大意

有 $n$ 张卡牌，第 $i$ 张上写着 $a_i$。```Conan``` 和 ```Agasa``` 轮流操作，```Conan``` 先手。
每回合中，玩家选择一张卡牌，然后移除它本身和所有点数严格小于它的卡牌。
如果玩家需要操作时已经没有卡牌了，他就输了。

## 2.思路分析

仔细看，这明显就是一道博弈论的题目。

显而易见的，如果所有的牌的数量都是偶数，那么不论先手如何取，后手都可以找到对称的方法来取，也就是说，只要先手可以取，后手就一定可以取，所以后手必胜。

同样的，一旦存在一个奇数，那么至少对于这一类型的牌后手最后是会找不到对称取法的，这样也就败了。


那么如何来看这种类型的牌是奇数还是偶数呢，那就可以用桶排了。

## 3.AC 代码（建议先自己想）
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int bu[100010];
int n;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		bu[x]++;//桶排
	}	
	for(int i=0;i<100010;i++){
		if(bu[i]%2==1){//如果是奇数
			cout<<"Conan";
			return 0;//结束程序
		}
	}
	cout<<"Agasa";
	return 0;
}
```
_THE END_

By wangyi_c

---

## 作者：q_sum (赞：1)

这是我在博弈论中做过的最简单的问题。

$Agasa$的获胜规则：$Agasa$太可怜了，如果所有牌当中有一种牌是单数个，$Agasa$就输了,否则$Agasa$就赢了。

纠正一下楼上的错误（其实是题目出锅）：后面的循环要从$0$开始，做到$mx$,变量$mx$记录的是纸牌编号最大值。

[不信的话请查AC记录](https://www.luogu.com.cn/record/32560381)

理清了思路，题目就迎刃而解了：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100001],mx,n;
int main()
{
    cin>>n;
    for  (int i=1;i<=n;++i)
    {
    	int x;
    	cin>>x;
    	++a[x];
    	mx=max(x,mx);//先在读入数组的时候记录纸牌最大的编号
	}
	for (int i=0;i<=mx;++i)//然后循环再从0做到
	   if(a[i]%2==1)
	   {
	   	cout<<"Conan";
	   	return 0;
	   }
	cout<<"Agasa";
    return 0;
}
```
附带：$Don't$ $copy$ $code$

---

## 作者：LiRewriter (赞：1)

一道被hack成sabi的结论题...甚至让我产生了退cf的冲动<br>

算了...还是自己太弱...~~为了少让后人受这道题的荼毒所以就姑且把原来的题解通俗的解释一下~~<br>

一个直观的感受是，如果能把所有的都拿掉，那么Conan就赢了。也就是，最大的A如果有1个，一定是Conan赢。<br>

但是如果有不是1个呢？比如说样例中的 3 3.这样的话，只能拿一个3就进入了Conan和Agasa的拉锯战，显然观察可以看到，最大数有奇数个那么Conan赢，否则Agasa赢。<br>

但是这样会被hack。~~数据强一点能死啊~~原因在哪？不妨看这样一组数据：2 3 3 <br>

如果柯南拿了2 3，那么拉锯的结果会是Agasa赢。但是如果Conan只拿了一个2呢？结果就是Conan赢了。<br>

再捏一组数据 比如2 2 3 3.这时候，赢的还是Agasa，因为Conan是没有办法找到一个数让他在拉锯中获胜的。也就是，如果次大数也是偶数个，仍然没有办法让Conan找到一个让他赢的关键的数。<br>

以此上溯，如果每个数都不给他可乘之机，那么Agasa才有可能赢。<br>

好了，到现在我们已经差不多分析完成了。因为我们发现，只有每个数都是出现偶数次，那么才会是Agasa赢。全称量词的否定是存在量词，所以只要存在一个数出现了奇数次那么Conan就赢了。<br>

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
#define N 100005
int n, tmp, ans;
int a[N];
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &tmp);
        ++a[tmp];
    }
    for(int i = 1; i <= N; ++i)
        if(a[i] % 2 == 1) 
            return puts("Conan"), 0;
    puts("Agasa");
    return 0;
}
```

---

## 作者：_WF_ (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF914B)
我们可以以贪心策略。

- 因为 ```Conan``` 先手，如果有一种牌为奇数，就选那张就能赢。

- 如果没有则是 ```Agasa``` 赢。

具体可用**桶排**实现。

### AC 代码
```
#include<bits/stdc++.h>
using namespace std;
map<int,int>id;
int n,x;
int main(){
	cin>>n;
	int v=0;
	for(int i=1;i<=n;i++){
		cin>>x;
		id[x]++;
		if(id[x]%2==1)v++;
		else v--;
	}	
	if(v)cout<<"Conan";
	else cout<<"Agasa";
	return 0;//by W_F
}
```



---

## 作者：Dreamerly (赞：0)

## 题目：[CF914B](https://www.luogu.com.cn/problem/CF914B)
## 题意：
有 $n$ 张卡牌，第 $i$ 张上写着 $a_i$ 。Conan 和 Agasa 轮流操作，Conan 先手。每回合中，玩家选择一张卡牌，然后移除它本身和所有点数严格小于它的卡牌。如果玩家需要操作时已经没有卡牌了，他就输了。假设双方玩家决顶聪明，请判断谁会赢。
## 思路：
开始详细讲解，全程高能。

**首先**，我们从每张牌都不一样开始推导：此时 Conan 先手，他只需取最大的那张就必胜。

**其次**，若有多张最大的牌： 

$I$ . 有奇数张最大的，那么 Conan 还是只需取最大的一张，剩下偶数张一样的牌，而到 Agasa 取了，一人一张，最后赢的还是 Conan 。

$II$ . 有偶数张最大的，如果 Conan 还是只需取最大的一张，剩下奇数张一样的牌，此时 Conan 就输了，但是也许还有其他可能，因此聪明的 Conan 并不会只看最大的牌。

**然后**，在 $II$ 的基础上，若有多张第二大的牌：

$1$ . 有奇数张第二大的，那么 Conan 只需取其中一张，留下**偶数张第二大的**和**偶数张最大的**。此时 Agasa 不论取一张**第二大的**还是**最大的**， Conan 都取相同的，由于此时 Agasa 先取，因此 Conan 必赢。

$2$ . 有偶数张第二大的，此时 Conan 不论取一张**第二大的**还是**最大的**， Agasa 都取相同的，由于此时 Conan 先取，因此 Agasa 必赢。

想到这里，我们的推导已经结束了。现在你不妨想想，在更多张的情况下， Conan 怎样才能赢？

## 结论：
只要其中有一种牌为奇数张， Conan 就会将那一堆变成偶数张， Conan 就必赢；反之， Agasa 就必赢。

## 代码：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){ 
	int num=0,sign=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') sign=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		num=(num<<3)+(num<<1)+(ch^48);
		ch=getchar(); 
	}
	return num*sign;
} 
void write(int x){ 
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
	return;
}
map<int,int> m;
signed main(){
	int n=read();
	int x;
	for(int i=1;i<=n;i++) m[x=read()]++;
	for(auto it=m.begin();it!=m.end();it++){
		if(it->second&1){
			puts("Conan");
			return 0;
		}
	}
	puts("Agasa");
	return 0;
} 
```

---

## 作者：wangkangyou (赞：0)

话不多说，

### 上干货：

`map<int,int>`

其实基本上大多数 OIer 们都知道这玩意儿，STL的其中之一，map 表。本质上好像是棵红黑树，能在 $O(\log n)$ 的时间复杂度内通过**键**来查询**值**。而这里的键似乎可以为非 `struct` 自定义结构体的变量，从某种意义上来说也可以理解为下标可以是 `string` 等类型为下标的数组，以时间代价解决了桶数组不能以实数、字符串等为下标问题。

下面是几种基本操作:（假设已经定义了一个 `map<int,int>` 的集合 `mp`）

插入**键为 $key$, 值为 $value$** 的元素：
1. 覆盖版(若已存在相同键值的元素，直接覆盖)：`mp[key] = value;`
2. 剔除版(若已存在相同键值的元素，不作任何操作)： `mp.insert({key, value});`

查询键 $key$ 所对应的值，并存入变量 $a$ 中： `a = mp[key];`

遍历集合 `mp`：
```cpp
map<int, int> :: iterator it;//定义迭代器；
for(it = mp.begin(); it != mp.end()/*注意必须是 !=*/; ++ it){
   cout << it -> first; //键
   cout << " ";
   cout << it -> second; //值
   cout << "\n";
}
```

好，知道了以上的三中种基本操作就足够了。

### 那在本题又有什么用处呢？

其实我们发现，对于所有的 $a_i$ 都保证了小于 $10 ^ 5$，所以理论上可以直接开桶数组记录。但万一数据超过了 $10 ^ 9$ 怎么办呢？这时候就需要 `map` 来救场了。因为 $1 \le n \le 10 ^ 5$，所以我们是可以给它做一个 $O(n \log n)$ 的算法的。

对于博弈论的解法其实无非就是楼上几位 dalao 的做法。只要有一种牌数量为奇数就是 Conan 赢，否则就是 Agasa 赢。

因为如果所有牌数量都为偶数，那么后手完全可以跟着先手取牌，结果一定就是后手赢。否则先手就可以利用某一奇数牌堆来交换自己与后手的顺序，再来步步跟，就一定是先手赢了。

```cpp
#include<bits/stdc++.h>
#define int long long
#define File(x) freopen(x".in","r",stdin),freopen(x".out","w",stdout)
using namespace std;
int read (){
   int sum = 0, f = 1;
   char ch = getchar ();
   for(;!isdigit (ch); ch = getchar ()) if (ch == '-') f = -1;
   for(;isdigit (ch); ch = getchar ()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
   return sum * f;
}
void write (int x){
   if (x < 0) putchar ('-'), x = -x;
   if (x > 9) write (x / 10);
   putchar ('0' + x % 10);
   return;
}
const int N = 1e6 + 10; 
int a[N];
map<int, int> mp;
signed main(){
   int n = read();
   for(int i = 1; i <= n; ++ i){
      a[i] = read();
      mp[a[i]] ++;
   }
   map<int, int> :: iterator it;
   for(it = mp.begin(); it != mp.end(); it ++){
      if(it -> second % 2 == 1){
       	 puts("Conan");
        return 0;
      }
   }
   puts("Agasa");
   return 0;
}
```

---

## 作者：NightTide (赞：0)

首先说结论：

> 对于题目中给出的 $a$，若满足所有的元素均为偶数，则后手必胜；否则先手必胜。

显而易见的，如果所有的牌的数量都是偶数，那么不论先手如何取，后手都可以找到对称的方法来取，也就是说，只要先手可以取，后手就一定可以取，所以后手必胜。

同样的，一旦存在一个奇数，那么至少对于这一类型的牌后手最后是会找不到对称取法的，这样也就败了。

那么代码就非常简单了。

```cpp
#include<bits/stdc++.h>
#define MAXN 100010
using namespace std;
int n;
int a[MAXN], cnt[MAXN];
int main(){
    scanf("%d",&n);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for(int i = 1; i <= n; i++) cnt[a[i]]++;
    for(int i = 1; i <= n; i++){
        if(cnt[a[i]] % 2){
            printf("Conan\n");
            exit(0);
        }
    }
    printf("Agasa\n");
    return 0;
}
```


---

## 作者：Aya_tt (赞：0)

这是一道简单的博弈论的题目，规律自然显而易见。

假如每个牌都有偶数个，Agasa 只需要和 Conan 拿一样数量的牌，Agasa 即可获胜。但是只要有个奇数的牌，Agasa 就无计可施了，最终无法移动卡牌。

Conan 是本游戏的先手，只要有一个牌是奇数个，Conan 就是胜利了，不信大家可以推一推，同理，除非所有的牌都是偶数个，Agasa 获胜。这也许就是先手的优越感吧。


就好比样例一，$4$，$5$，$7$ 的牌都只有一个，都是奇数，所以 Conan 获胜。而样例二中的牌只有 $1$，$1$ 有两张，是偶数，所以 Agasa 获胜。

代码实现可以用一个数组 $t$ 来记录每张牌的数量，在 ```for``` 循环里判断奇偶性，就很轻松得出来最后的赢家了。

代码：
```c
#include<bits/stdc++.h>
using namespace std;
int n,t[100010],maxn,minn;
int main(){
	cin >> n;
	for(int i = 1;i <= n;i++){
		int k;
		cin >> k;
		t[k]++;
		maxn = max(maxn,k);
	}
	for(int i = 0;i <= maxn;i++){
		if(!(t[i] % 2)){
			cout<<"Conan";
			return 0;
		}
	}
	cout<<"Agasa";
}
```


---

## 作者：__cht (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/CF914B)

我们发现，在没有任何数相同的情况下（如例一），只要先手直接拿最大的牌就能获胜。

我们不妨设所有的 $a_i$ 都是偶数。

**不论先手如何拿，后手都可以跟先手拿一样的牌，保证所有牌仍然是偶数。**

最后一定是后手获胜了。

而如果有一个牌是奇数个，那么到最后先手就不能取胜了。

于是开一个桶 $t$ 统计 $a_i$ 出现的次数，然后扫描一遍就行了。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n;
int a[N];
int t[N];
int main()
{
    cin >> n;
    for(int i = 0; i < n; i ++) cin >> a[i];
    for(int i = 0; i < n; i ++) t[a[i]] ++ ;
    for(int i = 0; i < n; i ++)
    {
        if(t[a[i]] % 2 == 1)
        {
            cout << "Conan" << endl;
            return 0;
        }
    }
    cout << "Agasa" << endl;
    return 0;
}
```

---

## 作者：huyangmu (赞：0)

这道题的正解是博弈论。

分两种情况讨论，如果每一种卡牌都有偶数个，那么 Agasa 可以采取模仿策

略，和 Conan 拿一样的牌，结果是 Agasa 获胜。不然 Conan 就可以拿最大的

奇数个的牌，结果是 Conan 获胜。

所以我们可以用桶来记录每种卡牌出现的次数，如果有奇数个的牌堆就是 

Conan 获胜，否则就是 Agasa 获胜。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=1e5+5;
int n,a[NR],cnt[NR];
int main (){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for (register int i=1;i<=n;++i){
		cin>>a[i];
		++cnt[a[i]];//用桶记录出现次数 
	}
	for (register int i=1;i<=100000;++i){
		if (cnt[i]%2==1) return cout<<"Conan"<<'\n',0;
	}
	return cout<<"Agasa"<<'\n',0;
}


---

