# Food Buying

## 题目描述

Mishka wants to buy some food in the nearby shop. Initially, he has $ s $ burles on his card.

Mishka can perform the following operation any number of times (possibly, zero): choose some positive integer number $ 1 \le x \le s $ , buy food that costs exactly $ x $ burles and obtain $ \lfloor\frac{x}{10}\rfloor $ burles as a cashback (in other words, Mishka spends $ x $ burles and obtains $ \lfloor\frac{x}{10}\rfloor $ back). The operation $ \lfloor\frac{a}{b}\rfloor $ means $ a $ divided by $ b $ rounded down.

It is guaranteed that you can always buy some food that costs $ x $ for any possible value of $ x $ .

Your task is to say the maximum number of burles Mishka can spend if he buys food optimally.

For example, if Mishka has $ s=19 $ burles then the maximum number of burles he can spend is $ 21 $ . Firstly, he can spend $ x=10 $ burles, obtain $ 1 $ burle as a cashback. Now he has $ s=10 $ burles, so can spend $ x=10 $ burles, obtain $ 1 $ burle as a cashback and spend it too.

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
6
1
10
19
9876
12345
1000000000```

### 输出

```
1
11
21
10973
13716
1111111111```

# 题解

## 作者：幻之陨梦 (赞：5)

$\textbf{解题思路：}$首先我们看到每当你花 $x$ 块钱你就能收到一个 $\dfrac{x}{10}$ （向下取整）块钱的优惠券。怎么用通俗的语言解释这句话呢？就是你花 $9$ 份钱能买 $10$ 份的东西，这样就得出了一个公式 $ans = (s / 0.9)$，还有一处要注意就是要向下取整，修改完公式后变成 $ans = (int)(s / 0.9)$

**AC code:**
```cpp
#include<cstdio>//为了节省，所以不开万能头文件
using namespace std;//标准数据库
int T,s,ans;
int main()
{
    scanf("%d",&T);//输入T组数据
    while(T--)
    {
        scanf("%d",&s);//输入你有的钱数
        ans=(int)(s/0.9);//运用公式求得答案
        printf("%d\n",ans);//输出答案
    }
    return 0;
}
```

---

## 作者：123456zmy (赞：3)

每次返还 $10\%$，将 $s$ 除 $0.9$ 然后输出即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,s;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&s);
		printf("%d\n",(int)(s/0.9));
	}
	return 0;
}
```

---

## 作者：Aehnuwx (赞：2)

官方题解给出的是 $O(t\log s)$ 的解法,但实际上我们可以做到单次查询 $O(1)$ 的 $O(t)$ 做法.

同样是贪心,可以看出,我们每次花费 $10$ 显然可以做到花费钱数最大化.

故 $\mathbf{ans}= \begin{cases} \lfloor \dfrac{s}{9} \rfloor \times 10 +s\bmod 9-1,9|s \\ \lfloor \dfrac{s}{9} \rfloor \times 10 +s\bmod 9, \rm Otherwise \end{cases}$

为什么在 $9|s$ 的时候需要最后减去一个 $1$ 呢?因为此时在最后一次操作时 $s$ 仅会剩下 $9$,如果仍然用 $\lfloor \dfrac{s}{9} \rfloor \times 10 +s\bmod 9$ 的话答案就会多出 $1$,所以要将这个 $1$ 减掉.

（然而可以用 $s+\lfloor \dfrac{s-1}{9} \rfloor$ 或 $\lfloor \dfrac{10s}{9} \rfloor$,比我写的强 100 倍...)

应该没有什么给代码的必要了吧...

---

## 作者：Cult_style (赞：1)



```
#include<bits/stdc++.h>
using namespace std;
int a,n,k;
int main(){
	cin>>n;
	int s=0;
	for(int i=1;i<=n;i++){
	    cin>>a;
	    k=0;
            //有多组数据，所以要清空
	    while(a>=10){
		s=a-(a%10);
		k+=s;
		a-=s;
		a+=s/10;
        	//看看能拿到多少钱
	    }
	    cout<<k+a<<endl;
            //k是赚到的钱，加上a就是得数
	}
	return 0;
}
```


---

