# Card Trick

## 题目描述

Monocarp has just learned a new card trick, and can't wait to present it to you. He shows you the entire deck of $ n $ cards. You see that the values of cards from the topmost to the bottommost are integers $ a_1, a_2, \dots, a_n $ , and all values are different.

Then he asks you to shuffle the deck $ m $ times. With the $ j $ -th shuffle, you should take $ b_j $ topmost cards and move them under the remaining $ (n - b_j) $ cards without changing the order.

And then, using some magic, Monocarp tells you the topmost card of the deck. However, you are not really buying that magic. You tell him that you know the topmost card yourself. Can you surprise Monocarp and tell him the topmost card before he shows it?

## 说明/提示

In the first testcase, each shuffle effectively swaps two cards. After three swaps, the deck will be $ [2, 1] $ .

In the second testcase, the second shuffle cancels what the first shuffle did. First, three topmost cards went underneath the last card, then that card went back below the remaining three cards. So the deck remained unchanged from the initial one — the topmost card has value $ 3 $ .

## 样例 #1

### 输入

```
3
2
1 2
3
1 1 1
4
3 1 4 2
2
3 1
5
2 1 5 4 3
5
3 2 1 2 1```

### 输出

```
2
3
3```

# 题解

## 作者：En_ligne (赞：2)

[题面](https://www.luogu.com.cn/problem/CF1681B)
## 题意
给出一个长度为 $n$ 的数组，进行 $m$ 次操作，每次把数组前 $b_j$ 个元素放到数组最后面，求操作完后数组的第一个元素。
## 思路
定义一个 $pot$ 指针用于指向**当前的数组第一个元素**，注意不要直接用循环队列模拟，会炸掉。
#### 代码中的注意事项
 $pot$ 不要越界。
 
因为有多组数据，所以每组数据处理完要清空我们的数组。
##  AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000005];
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n,m;
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		scanf("%d",&m);
		int pot=1;
		for(int i=1;i<=m;i++)
		{
			int x;
			scanf("%d",&x);
			pot+=x;
			if(pot>n) pot-=n;//不能让pot越界,用指针的循环模拟数组的循环
		}
		printf("%d\n",a[pot]);
		memset(a,0,sizeof(a));//注意一定要清空数组
	}
	return 0;
}
```

---

## 作者：cxy000 (赞：2)

题目大概是这样的：

输入数字，定义一个指针，在出入的时候移动指针即可。

比如样例 $1$：

定义数组 $a$，初始顺序为 $x_1=1$，$x_2=2$。

然后 $xx$ 指向 $1$，这是初值。

将 $x_1$ 向后调，则此时第一个元素为 $x_2$，故 $xx$ 为 $2$。

以此类推，以指针的活动代替数组的运动（数组不变）。

记住：不要用队列，会爆掉。

记得取模，因为指针 $xx$ 可能会大于 $n$，故要记得取模哦。

还有一点，当去完模后若 $xx$ 为 $0$，记得设为 $n$。

所以没有坑了。

```
#include <bits/stdc++.h>
using namespace std;
int a[1000100];
int main(){
	int t;
	cin>>t;
	int n,m;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		int x,xx=1;
		cin>>m;
		for(int i=1;i<=m;i++){
			cin>>x;
			xx+=x;
			xx%=n;
		}
		if(xx==0) xx+=n;
		cout<<a[xx]<<endl; //记得不是输出xx
	}
	return 0;
}
```


---

## 作者：sssscy_free_stdio (赞：1)

蒟蒻又来写题解了~

本题看着很复杂，其实直接用一个指针 $p$ 来模拟就可以解决了

就是每次输入一个 $b_i$， 就把 $p$ 加上 $b_i$ 就行了，但是要判断 $p$ 大于 $n$ 的情况，用一个 `if` 就好啦~

AC CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
int a[200010],b[200010];
int main(){
	scanf("%d",&t);
	while(t --> 0){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}scanf("%d",&m);
		for(int i=1;i<=m;i++){
			scanf("%d",&b[i]);
		}int now=1;
		for(int i=1;i<=m;i++){
			now+=b[i];
			if(now>n){//p大于n的情况
				now-=n;//阻止越界
			}
		}printf("%d\n",a[now]);
	}
	return 0;
}

---

## 作者：szh_AK_all (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1681B)

## 题意加分析
有一个长度为 $n$ 的序列，将其操作 $m$ 次，每一次操作可以将序列的前 $k$ 个元素移到数组的后方，求操作完后，序列的第一个元素是什么。

既然每次操作是将序列的前 $k$ 个数移到后面，那么我们可以将序列看成是一个圆排列，虽然元素移动了位置，但本质的顺序还是不变的。因为我们访问完序列后，又会回到原来被移动的元素，这样，原来（不改变）的顺序是：前->后。而现在（改变了）的顺序是：后->前->后，所以本质的顺序还是不变的。

既然无论怎么操作，本质的顺序是不变的，那么在每次操作时，我们将元素移动到后面，只是将指向第一个元素的指针向后（也就是数组的右方）移动了，如果指针指向的位置越界了，指针仍会指向原来的元素（也即被移动的元素）。所以，在每次操作时，我们将前 $k$ 个元素移动，那么指针也要移动 $k$ 个位置，就这样不断操作，如果指针指向的位置大于数组的长度，那么就将指针指向的位置模上 $n$ 即可。

## Code
```c
#include<iostream>
using namespace std;
int a[200005];
int main()
{
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        int n;
        cin>>n;
        for(int i=1;i<=n;i++)
            cin>>a[i];
        a[0]=a[n];
        int m;
        cin>>m;
        int z=1;
        for(int i=1;i<=m;i++)
        {
            int x;
            cin>>x;
            z=(z+x)%n;
        }
        cout<<a[z]<<endl;
    }
}
```
可以注意到第 $25$ 行，之所以加这一句，是因为在指针模 $n$ 是，答案可能为 $0$（$n \bmod n=0$），所以，当指针指向第 $0$ 个位置时，就相当于指向第 $n$ 个位置。

---

## 作者：Night_sea_64 (赞：1)

大家好，本蒟蒻又来写题解了~

[题目](https://www.luogu.com.cn/problem/CF1681B)

我们先来看看样例。

拿 $a=\{3,1,4,2\}$ 为例。将会执行 $2$ 次操作：

第 $1$ 次，$b=3$，$a$ 变为 $\{2,3,1,4\}$；

第 $2$ 次，$b=1$，$a$ 变为 $\{3,1,4,2\}$；

我们发现，这个操作正好可以用 STL 中 $\operatorname{rotate}$ 函数来实现。不会的可以自行百度。

但是这个函数的时间复杂度是 $O(n)$ 的。如果直接在输入的每条操作里执行这个函数，总时间复杂度将会是 $O(t\times m\times n)$，肯定会 TLE。怎么办呢？

我们再回过头来看看样例。执行完第 $2$ 次操作后，所得的数组和原来一样。为什么呢？把这两次操作合起来看，不就是一个 $b$ 为 $4$ 的操作吗？而我们 $\operatorname{rotate}$ 函数就是一个旋转数组元素的函数，转了 $4$ 回之后，所得的数组当然和原来相同啊！

那么这样就好办了。我们用一个 $sum$ 求出每个操作里 $b$ 的和，然后根据刚才提到的 $\operatorname{rotate}$ 函数的性质，将 $sum\gets (sum \bmod n)$，所得的数组一定和原来一样。就和那道大家所熟知的 [P1076](https://www.luogu.com.cn/problem/P1076) 有点像。

AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200010];
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        for(int i=1;i<=n;i++)cin>>a[i];
        int m,sum=0;
        cin>>m;
        for(int i=1;i<=m;i++)
        {
            int b;
            cin>>b;
            sum=(sum+b)%n;
        }
        rotate(a+1,a+sum+1,a+n+1);
        cout<<a[1]<<endl;
    }
    return 0;
}
```

蒟蒻语文不好，不懂的可以私信。

---

## 作者：qwq___qaq (赞：1)

可以发现，本题是一个环状结构，那么，我们可以发现，移动 $n$ 次后又会变为原状，那么答案就是 $a_{\sum\limits_{i=1}^nb_i\bmod n}$。

[Code](https://codeforces.com/contest/1681/submission/158343006)

---

## 作者：happy_dengziyue (赞：1)

### 1 视频题解

![](bilibili:BV1T541197NA)

### 2 思路

我们设 $ans$ 为顶端的牌的编号，初始为 $1$。

我们可以发现，每次让 $b$ 张上面的牌移到下面，就会使得 $ans$ 往右移 $b$ 位。

那么我们依照题意模拟即可。注意取模问题。

### 3 代码与记录

```cpp
#include<cstdio>
using namespace std;
#define max_n 200000
int t;
int n;
int a[max_n+2];
int q;
int ans;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1681B_1.in","r",stdin);
	freopen("CF1681B_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)scanf("%d",a+i);
		scanf("%d",&q);
		ans=1;
		for(int i=1,x;i<=q;++i){
			scanf("%d",&x);
			ans=(ans+x)%n;
		}
		if(!ans)ans=n;
		printf("%d\n",a[ans]);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/76377438)

By **dengziyue**

---

## 作者：mxxby (赞：0)

~~我跋山涉水，千辛万苦写了一篇题解。~~

随手写一篇题解。

**[题目内容](https://www.luogu.com.cn/problem/CF1681B)**

# 题目简介

$t$ 组数据，每组数据给出包含 $n$ 个数字的序列，$m$ 次操作，每次操作将数组前 $b_j$ 个数挪到最后面。

# ~~仅剩的一点~~思路

对于将前 $b_j$ 个数挪到后面，等价于将指向第一个元素的指针往后移。

挪到最后则再从头开始。

为什么呢？

~~根据前后相对论~~，你的对手退步了，你就进步了，所以当你前面的挪到你后面了，你就到前面了~~十分的贴切~~。

好好地举个栗子：

- $1\ 2\ 3\ 4\ 5$ 初始状态。

- $2\ 3\ 4\ 5\ 1$ 挪 $1$ 个：$1$ 到最后，$2$ 到最前面。

- $3\ 4\ 5\ 1\ 2$ 挪 $2$ 个：$1\ 2$ 到最后，$3$ 到最前面。

- $4\ 5\ 1\ 2\ 3$ 挪 $3$ 个：$1\ 2\ 3$ 到最后，$4$ 到最前面。

- $5\ 1\ 2\ 3\ 4$ 挪 $4$ 个：$1\ 2\ 3\ 4$ 到最后，$5$ 到最前面。

- $1\ 2\ 3\ 4\ 5$ 挪 $5$ 个：$1\ 2\ 3\ 4\ 5$ 到最后，$1$ 到最前面。

就好比一个环，再怎么挪动，环内元素的顺序是不变的。

就可以用个累加求和啦。

## ~~蒟蒻的~~代码

```cpp
#include<bits/stdc++.h>
#define lon long long//用来装×（毕竟蒟蒻--我当时不知道这个，所以觉得很酷）
using namespace std;
lon t,n,a[200010],m,gs,s;//n 上限 2e5 数组记得开大（别像我一样）
 int main(){
	scanf(" %lld",&t);
	for(int i=1;i<=t;i++){
		gs=1;//一开始指向1
		scanf(" %lld",&n);
		for(int j=1;j<=n;j++) scanf(" %lld",&a[j]);//输入数组
		scanf(" %lld",&m);
		for(int j=1;j<=m;j++) scanf(" %lld",&s),gs+=s; //将m个数累加
		printf("%lld\n",a[ gs%n ==0 ? n : gs%n]);//小小的取模
	}//多组数据记得换行
	return 0;//收拾残局
}
```

~~蒟蒻的第二篇题解五审，求过 qwq。~~

---

## 作者：awaken1802 (赞：0)

### 题意：
给出一个长度为 $n$ 的序列 $a$，$m$ 次操作，每次读入一个数 $b$，把下标为 $1$ 到 $b$ 的数列移动到下标为 $b$ 到 $n$ 的数列后面。
### 思路：
第一次操作后，这个数列的第一个元素下标就是 $b$,因为有多组数据，所以 $m$ 次操作过后第一个元素的下标就是每次操作读入的 $b$ 的和（可以用一个变量 $jilu$ 累加），为了防止下标溢出，我们的解决方案就是每一次累加都要 $jilu \bmod n$。最后输出这个下标和所对应的数。
### 注意事项：
$1$：取模运算有可能使结果变成 $0$，这时我们要输出 $a_n$。

$2$：因为有多组测试数据，所以每次都要清空累加器。
### 代码实现：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long t,n,m,a[200010],tmp,jilu;
int main(){
	scanf("%lld",&t);
	for(long long i=1;i<=t;i++){
	    scanf("%lld",&n);
	    jilu=1;
	    for(long long j=1;j<=n;j++)scanf("%lld",&a[j]);
	    scanf("%lld",&m);
	    for(long long j=1;j<=m;j++){
		    scanf("%lld",&tmp);
	            jilu+=tmp;
	            jilu%=n;
	   }
	   if(jilu>0)printf("%lld\n",a[jilu]);
	   else printf("%lld\n",a[n]);
	}
	return 0;
}

```


---

## 作者：xxxalq (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF1681B) & [CF链接](http://codeforces.com/problemset/problem/1681/B)

## 思路分析：

我们只需要把这个数列看成一个环，设一个变量表示数列第一个数字的下标，每次加上 $b_j$ 再取模 $n$ 即可，注意数组下标要从 $0$ 开始，这样取模 $n$ 之后余数就是 $0$ 到 $n-1$ 了。

## 代码：

```cpp
#include<iostream>
using namespace std;
int n,m,a[200010];
int main(){
	int T,t,idx;
	cin>>T;//T组数据
	while(T--){
		idx=0;//指针初始化
		cin>>n;
		for(int i=0;i<n;i++){
			cin>>a[i];
		}
		cin>>m;
		while(m--){
			cin>>t;
			idx=(idx+t)%n;//移动指针
		}
		cout<<a[idx]<<endl;//输出
	}
	return 0;
}
```

---

## 作者：ZHANGyutao123 (赞：0)

# CF1681B Card Trick 题解
## [题目传送门](https://www.luogu.com.cn/problem/CF1681B)
## 题目大意
有一个牌堆，其中卡牌的值从顶部到底部依次为 $a_1, a_2, \dots, a_n$，且所有值不重复。

然后进行了 $m$ 次洗牌操作，每次操作将 $b_j$ 张顶部的牌移到剩余的 $(n-b_j)$ 张牌的下方，保持牌的顺序不变。

现在要求你根据洗牌后的顺序，预测最上面的那张卡牌的值。
## 分析
如果直接模拟，就会超时，~~毕竟我试过~~。

既然不能直接模拟，可以试着找规律。

假设旧位置为 $x$，移动的牌数为 $b_j$，新位置为 $y$。洗牌操作将从旧位置的卡牌移到新位置上。因为卡牌是按顺时针方向移动的，所以当旧位置加上移动的牌数后再取模卡牌总数，就是新位置 $y$。

当洗牌操作进行时，每次操作只会影响最上面的那张卡牌的位置。我们可以将牌堆的编号进行重新排列，从而使得旧位置 $x$ 对应新位置 $y$，即 $y = (x + b_j) \bmod n$。

#### 证明：

根据洗牌操作的规则，移动的牌数为 $b_j$，则旧位置 $x$ 上的卡牌将向右移动 $b_j$ 个位置。由于牌堆是循环的，当超过 $n$ 时，会重新回到起点继续移动。

因此，我们可以将旧位置 $x$ 加上移动的牌数 $b_j$，得到一个临时的新位置   $x' = x + b_j$。

然而，此时我们还需要考虑新位置是否在合理范围内。如果 $x'$ 超过了卡牌总数 $n$，我们需要将其减去 $n$，以确保新位置仍在有效范围内。

最终的新位置 $y = x' \bmod n$ 即为洗牌后最上面的卡牌所处的位置。

综上所述，我们得到了公式 $x = (x + b_j) \bmod n$。这个公式说明了洗牌操作后最上面的卡牌位置的变化规律。
## 参考代码
```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;

        vector<int> deck(n);
        for (int i = 0; i < n; i++) {
            cin >> deck[i];
        }

        int m;
        cin >> m;

        int offset = 1;  

        for (int i = 0; i < m; i++) {
            int move;
            cin >> move;

            offset += move;
            offset %= n;

            if (offset == 0) {
                offset = n;
            }
        }

        cout << deck[offset - 1] << endl;
    }

    return 0;
}
```


---

## 作者：_VEGETABLE_OIer_xlc (赞：0)

[题目传送门](https://www.luogu.com.cn/blogAdmin/article/new#CF1681B)

# 详细版题意

给定一个长度为 $n$ 的数组 $a$，长度为 $m$ 的数组 $b$，执行如下操作：将前 $b_i$  个数移到 $a$ 数组的后面。操作 $m$ 次，问操作完开头的数是多少。

**注意此题多测**。

很明显，直接去将数组中的元素**直接进行操作**，肯定是**不切合实际**的，单次操作复杂度高，会超时。

#### 分析

既然我们不能将数组**整体进行改变**，那我们可不可以拿出数组中的**一个个体**进行移动，这样能大大减少时间复杂度。

再看回问题，他只让我们求打头的数，并没有让我们输出整个数组，**方法可行**！

我们可以用一个变量 $c$ 来记录数组打头数的下标，移动完输出不就完事了吗？肯定不会超时。

有了方法代码实现就很容易了，变量 $c$ 每次加 $b_i$，发现超出 $n$ 就取一次模即可。

上代码！
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200010],m,b[200010];
int main(){
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		int c=1;
		cin>>m;
		for(int i=1;i<=m;i++)
		{
			cin>>b[i];
			c+=b[i];//此时第m+c的下标的数在最前面
			c%=n;
		}
		if(c==0)c+=n;
		cout<<a[c]<<endl;//输出是有着极其吉利的寓意的（
	}
	return 0;
}
```
本题结束。提交代码，我们很快如本代码的输出一样 AC 了这道题。

[记录。](https://www.luogu.com.cn/record/113467312)

看完真是后怕。这样优化时间还是达到了 $514ms$，~~成功取得最差解~~，再次证明不优化肯定会超时。

再见！

---

## 作者：lmndiscyhyzdxss (赞：0)

## 题目大意
给定一个长度为 $ n $ 的数组，对其进行 $ m $ 次操作，每次操作是一个数 $ b_j $，意思是将数组前 $ b_j $ 个元素放到数组最后面。问执行完操作后数组第一个元素是啥。
## 题目分析
首先，直接模拟题目中的各个步骤的移动，用队列最好，但题目中有个 $ T $，时间复杂度应该是 $ O\left(Tnm \right) $，肯定会超时。

其实，题目只要求第一个数是啥，那我们只要关注第一个数就好了。我们可以定义一个指针 $ l $，每次操作 $ b $ 个数，就向后移动 $ b $ 格，即 ``` l+=b ```，如果超过了 $ n $，就 ``` l%=n ```。但是，如果 $ l=n $，这种方法就不行了，有三种解决办法。

1. 加入特判

特判 $ l=n $ 的情况，则将 ``` l=n ```。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000010],t,n,m,b,l;
int main(){
	cin>>t;
	while(t--)
	{
		cin>>n,l=1;
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		cin>>m;
		for(int i=1;i<=m;i++)scanf("%d",&b),l+=b,l%=n;
		if(l==0)l=n;//特判
		cout<<a[l]<<endl;
	}
	return 0;
}
```
2. $ -1 $ 大法

这个题可以用 ``` l=(l-1)%n+1 ``` 这个公式来解决，因为 $ l-1<n $，$ (l-1)\bmod n=l-1$，$ (l-1)\bmod n+1=l-1+1=l $。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000010],t,n,m,b,l;
int main(){
	cin>>t;
	while(t--)
	{
		cin>>n,l=1;
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		cin>>m;
		for(int i=1;i<=m;i++)scanf("%d",&b),l+=b,l=(l-1)%n+1;
		cout<<a[l]<<endl;
	}
	return 0;
}
```
3. 提前赋值

提前把 $ a_0 $ 赋值 $ a_n $，即 ``` a[0]=a[n] ```，即使 $ l=0 $，也会输出 $ a_n $ 的值，不是 $ 0 $。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000010],t,n,m,b,l;
int main(){
	cin>>t;
	while(t--)
	{
		cin>>n,l=1;
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		cin>>m,a[0]=a[n];//赋值
		for(int i=1;i<=m;i++)scanf("%d",&b),l+=b,l%=n;
		cout<<a[l]<<endl;
	}
	return 0;
}
```

---

## 作者：Youngxin (赞：0)

### 题目简述
给定一种操作，把前 $i$ 个数移动到数组末尾且不改变顺序，求数组的开头数。
### 思路
如果是单纯模拟，根据多组数据和数组的移动这些操作，时间复杂度为 $O(knm)$，并非可行解。

所以我们观察题目，求的是数组的开头数，那就好做了。维护开头的指针，将移动的操作改成移动指针，时间复杂度为线性，可以通过此题。

详细操作：设指针为 $p$，数组有 $n$ 个数，若是将前 $i$ 个数移动到末尾，则让 $p$ 加上 $i$，若是 $p>n$，则对 $p$ 取模，详细代码如下：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N = 1000010;
int a[N];
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n,m,x,p = 1;
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		scanf("%d",&m);
		for(int i=1;i<=m;i++){
			scanf("%d",&x);
			p += x;
			if(p == n) continue;
			else p %= n;
		}
		printf("%d\n",a[p]);
	}
	return 0;
}
```


---

## 作者：xiaofeng_and_xiaoyu (赞：0)

[题目](https://www.luogu.com.cn/problem/CF1681B)

看到题目一开始以为是队列，打到一半想起了数据范围，一看：

诶？怎么还有个 $\verb!t!$ 啊？

![（当时的）情景](https://cdn.luogu.com.cn/upload/image_hosting/miabrfev.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

于是我发布了[这个帖子](https://www.luogu.com.cn/discuss/604823)，然后重新考虑了算法。

用队列肯定是不行了，肯定会爆，不过它还是好像循环队列啊，一直把下标动来动去。

嗯？下标？

既然只是下标在变，那么我们只需要把按照下标的变化进行改变就行了，省去了许多次进出队列的时间。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a;
	cin>>a;
	while(a--){//多组数据
		int t,ans=1;//注意下标从1开始	
		cin>>t;
		int l[t+1];
		for(int i=1;i<=t;i++){
			cin>>l[i];
		}
		int q,m;
		cin>>q;
		for(int i=0;i<q;i++){
			cin>>m; 
			ans+=m;
			if(ans>t){
				ans-=t;//如果越界，要及时返回
			}
		}
		cout<<l[ans]<<endl;
	}
	return 0;
}
```


---

## 作者：LeTu_Jun (赞：0)

## 题意

进行 $m$ 次将 $a$ 数组前 $b_j$ 个元素挪到最后面的操作，求最后数组第一位的值。

本题多组数据。

## 思路

首先直接模拟肯定不行。总复杂度 $O(Tmn)$，TLE 不是怪事。

那么，如何维护数组呢？

发现虽然操作次数很多，但是实际上只求数组第一位的值。所以直接放一个指针 $x$ 维护即可。

注意指针 $x$ 初始值为 $1$。

第 $i$ 次操作将 $x$ 加上 $b_i$ 即可。

但需要注意的是 $x$ 很可能会大于 $n$，造成越界。所以每次操作后 $x$ 要对 $n$ 进行一个取模，防止越界。

但是即使补上了取模仍然会 WA，这是因为 $x \bmod n$ 的范围是 $0$ 至 $n-1$，而显然当 $x \bmod n = 0$ 时 $x$ 就在数组的第 $n$ 位。这点需要注意。

最后就是 CF 的题大部分都多组数据，记得每组数据都要清空数组。

代码变量意义同文字。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int a[N];
int n,m,x=1;
int t;
int main ()
{
	scanf("%d",&t);
	while(t--){
		memset(a,0,sizeof(a));
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",a+i);
		}
		scanf("%d",&m);
		for(int i=1;i<=m;i++){
			int b=0;
			scanf("%d",&b);
			x+=b;
			x=x%n;
			if(x==0)
			{
				x=n;
			}
			//printf("!!x: %d\n",x);
		}
		//printf("ans:%d",x);
		printf("%d",a[x]);
	}
	return 0;
}
```


---

## 作者：cyrxdzj (赞：0)

### 一、思路

首先，假想一个指针，一开始指向 `a` 数组的第一个数字。

我们可以发现，执行第 $i$ 次 `shuffle`（原文如此），就是执行 $b_i$ 次操作；执行一次操作，其实就是将指针向右移动一个数字。如果指针越过了 `a` 数组的范围，则将进行循环，将指针回到一。

因此，代码就不难写了。

### 二、代码

```cpp
#include<cstdio>
using namespace std;
int t;
int n,m;
int a[200005];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
		}
		scanf("%d",&m);
		int index=1;//指针
		for(int i=1;i<=m;i++)
		{
			int x;
			scanf("%d",&x);
			index+=x;//移动指针
			index%=n;//取余
		}
		if(index==0)//指针为零时
		{
			index+=n;//将指针设置为 a 数组的最后一个数
		}
		printf("%d\n",a[index]);
	}
	return 0;
}

```


---

## 作者：cfkk (赞：0)

前置芝士：贪心。

注意到每次取的牌顺序不变放入排堆尾部，因此是一个循环，于是交换总和除以牌总数的余数 $sum\pmod n$ 即等效交换次数，而对应的数组元素即交换后的牌顶元素。

时间复杂度 $O(n)$

空间复杂度 $O(n)$

所以我们按操作进行模拟即可。

代码来喽：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define min(a,b)(a<b?a:b)
#define max(a,b)(a>b?a:b)
#define mod 998244353
#define int long long
inline int read()
{
    char ch=getchar();
    int s=0,w=1;
    while(ch<'0'||ch>'9')
    {
        if(ch=='-'){w=-1;}
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        s=(s<<1)+(s<<3)+ch-48;
        ch=getchar();
    }
    return w*s;
}
inline void out(int x)
{
    if(x<0){putchar('-'),x=-x;}
    if(x>9){out(x/10);}
    putchar(x%10+'0');
}
inline void print(int x)
{
    out(x);
    putchar('\n');
}
inline string read_char()
{
    string str="";
    while(1)
    {
        char ch=getchar();
        if(ch=='\n'){break;}
        str+=ch;
    }
    return str;
}
int n,m;
int a[222222];
signed main()
{
    int T=read();
    while(T--)
    {

        int n=read();
        for(int i=0;i<n;i++){a[i]=read();}
        int m=read(),pos=0;
        for(int i=0,b;i<m;i++)
        {
            b=read();
            pos=(pos+b)%n;
        }
        print(a[pos]);
    }
	return 0;
}

```


---

