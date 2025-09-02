# Wizard of Orz

## 题目描述

There are $ n $ digital panels placed in a straight line. Each panel can show any digit from $ 0 $ to $ 9 $ . Initially, all panels show $ 0 $ .

Every second, the digit shown by each panel increases by $ 1 $ . In other words, at the end of every second, a panel that showed $ 9 $ would now show $ 0 $ , a panel that showed $ 0 $ would now show $ 1 $ , a panel that showed $ 1 $ would now show $ 2 $ , and so on.

When a panel is paused, the digit displayed on the panel does not change in the subsequent seconds.

You must pause exactly one of these panels, at any second you wish. Then, the panels adjacent to it get paused one second later, the panels adjacent to those get paused $ 2 $ seconds later, and so on. In other words, if you pause panel $ x $ , panel $ y $ (for all valid $ y $ ) would be paused exactly $ |x−y| $ seconds later.

For example, suppose there are $ 4 $ panels, and the $ 3 $ -rd panel is paused when the digit $ 9 $ is on it.

- The panel $ 1 $ pauses $ 2 $ seconds later, so it has the digit $ 1 $ ;
- the panel $ 2 $ pauses $ 1 $ second later, so it has the digit $ 0 $ ;
- the panel $ 4 $ pauses $ 1 $ second later, so it has the digit $ 0 $ .

The resulting $ 4 $ -digit number is $ 1090 $ . Note that this example is not optimal for $ n = 4 $ .

Once all panels have been paused, you write the digits displayed on them from left to right, to form an $ n $ digit number (it can consist of leading zeros). What is the largest possible number you can get? Initially, all panels show $ 0 $ .

## 说明/提示

In the first test case, it is optimal to pause the first panel when the number $ 9 $ is displayed on it.

In the second test case, it is optimal to pause the second panel when the number $ 8 $ is displayed on it.

## 样例 #1

### 输入

```
2
1
2```

### 输出

```
9
98```

# 题解

## 作者：sheeplittlecloud (赞：3)

## Part 0 翻译补充
题目翻译中没有输入输出数据翻译，所以可能会让大家有些懵，所以这里给出翻译：    
**输入格式：**    
第一行一个 $t$ 表示数据组数。      
接下来 $t$ 行，每行有一个数 $n$ ,表示面板的面数。    

**输出格式：**      
$t$ 行，每行一个 $n$ 位数，意义见题目       


------------
## Part 1 思路推导 
由于每块面板可以表示 $0$ ~ $9$的数，我们又要让结果最大，所以理所当然，我们要将第一位变为 $9$ 。      
所以顺着往下想，就可以想到当 $1$ 号面板为 $9$ 时，按下暂停键。    
这时的数为：      
$$901234567...$$     
这时大家会发现，第二位太小了。     
有什么解决方法吗？      
在题面中有一句话：    
`然后，与之相邻的面板在1秒钟后暂停`    
所以，我们可以将 $2$ 号面板在当它的数值为 $8$ 时，暂停。     
这样既可以保证第一位不小，也可以保证第二，三位够大。       

## Part 2 代码实现 
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t,n,i;
	cin>>t;
	while(t--)
	{
		cin>>n;
		if(n==1) 
		{
			cout<<9<<endl;//特判
			continue;
		}
		cout<<9;//先输出第一位的9
		int x=8;//从第二位起，后面的数都是递增，所以从8开始
		for(i=2;i<=n;i++)//从二开始
		{
			cout<<x;
			x++;
			if(x>=10) x=0;//当数到了10的时候，就要变为0
		}
		cout<<endl;//这一步很重要！（我就是因为这个而没有一遍过的）
	}
	return 0;
}

```
完结撒花！

---

## 作者：qinyihao (赞：2)

## 思路
如果只有一个数字面板，那么当它显示$9$的时候，应该将其暂停，这应该是最优解了。否则，最优解应该永远是在数字$8$显示时，将左起第二个数字面板暂停。这种情况的输出格式是`989012345678901234567...`

这可以被证明是可以被归档的最大数值。

## code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int solveTestCase() {
    int n;
    cin >> n;

    string s = "989";
    if (n <= 3)
        return cout << s.substr(0, n) << "\n", 0;

    cout << s;
    for (int i = 3; i < n; i++)
        cout << (i - 3) % 10;
    cout << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--)
        solveTestCase();
}
```

---

## 作者：lndjy (赞：1)

基础构造题。

考虑想让一个数最大，那么首先让最高位最大，必须是 $9$。

那么就有一种方案：$9012345...$。

然而这并不是最优的，因为第二位它太小了。有没有办法能让第二位也大一点呢?是有的，我们让第二位从 $8$ 停止，这样第一位还是 $9$，第二位就变成 $8$ 了。

所以答案为 $98901234...$。

```cpp
#include<iostream>
using namespace std;
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n;
		if(n<=2)
		{
		int now=9;
		for(int i=1;i<=n;i++)
		{
			cout<<now;
			now--;
			if(now<0) now=9;
		}
		cout<<endl;
		}
		else
		{
			n-=3;
			cout<<"989";
		int now=0;
		for(int i=1;i<=n;i++)
		{
			cout<<now;
			now++;
			if(now>9) now=0;
		}
		cout<<endl;
		}
	 } 
 	return 0;
}


```


---

## 作者：Biuld (赞：0)

~~本蒟蒻第一次写题解，求关照~~

这题是朋友推荐给我的一道‘水题’，也确实很水，~~我花了半个多小时才做出来~~。

以上为废话
我第一眼看题，以为是一道有关回文数的题，看完题才发现，这是一道水题。（~~还用你说，废话~~）

相信有很多朋友看完题后，和我一样，看不懂输入和输出。 我当时在输入格式和输出格式上琢磨了很久，终于看懂了输入输出。

输入
第一行输入一个整数$n$，表示问题的个数。 接下来的$n$行，每行一个整数$m$，表示面板的个数。

输出
输出一共$n$行，每行输出一个数；

反正就是输出当面板暂停时，获得的最大数。

先枚举一下这题的答案：

面板数为$1$时，答案是$9$；

面板数为$2$时，答案是$98$；

面板数为$3$时，答案是$989$；

面板数为$4$时，答案是$9890$；

面板数为$5$时，答案是$98901$……

不难发现，答案在从第二位往后，都是有规律的。（你们应该都看得出来吧）~~还不是懒得写~~

代码
你们最喜欢的部分
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int s;
        scanf("%d",&s);
        if(s==1) printf("9");
        else if(s==2) printf("98");
        else
        {
            printf("98");
            a=9;
            for(int j=3;j<=s;j++)
            {
                printf("%d",a);
                a++;
                if(a==10) a=0;
            }
        }
        printf("\n");
    }
    return 0;
}
```
代码大家应该都看得懂，我就不作过多解释了 ~~懒得写~~（你们还是要多自己动脑思考，不要只抄代码哦）

---

## 作者：Refined_heart (赞：0)

比较简单的构造题。

注意到我们只能让一个位置先停止。

观察样例$2$，发现让第二个数在$8$的时候停下可以保证前三位数是最大的$989$.

于是对于任意$n\ge 3$一定是让第二个数为$8$的时候停下。

第二位往左就是一个无脑的$\bmod 10$意义下的加法了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		if(n==1)puts("9");
		else if(n==2)puts("98");
		else{
			int p=9;
			printf("98");
			for(int i=3;i<=n;++i){
				printf("%d",p);
				p++;p%=10;
			}
			puts("");
		}
		//puts("");
	}
	return 0;
} 
```

---

## 作者：wmy_goes_to_thu (赞：0)

pause 第一个点，答案是 $90123...$

pause 第二个点，答案是 $98901...$

pause 第三个点，答案是 $98789...$

再往后 pause，都是 $987...$

所以 pause 第二个点答案最优，是 $98901234567...$

---

