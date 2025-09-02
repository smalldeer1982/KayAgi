# Position in Fraction

## 题目描述

给你三个整数 $a,b,c$，问 $\dfrac{a}{b}$ 的小数部分第几位是 $c$，如果无法找到，请输出 `-1`。

## 说明/提示

对于 $100\%$ 的数据：$1\le a<b\le 10^5,0\le c\le 9$。

## 样例 #1

### 输入

```
1 2 0
```

### 输出

```
2```

## 样例 #2

### 输入

```
2 3 7
```

### 输出

```
-1```

# 题解

## 作者：fls233666 (赞：4)

显然，为了确定 $\frac{a}{b}$ 的小数部分，我们要**模拟做除法的过程**。

考虑无解的情况，应该是出现了无限循环小数。那么问题变为如何判断出现了循环节？

考虑除法的全过程，我们发现，**当 $a$ 除以 $b$ 的余数出现重复时，就会出现循环节**。

针对此特点和数据范围，开一个大小为 $10^5$ 的数组记录 $a$ 除以 $b$ 的每个余数是否有出现过。循环模拟除法过程并判断，当某一余数出现了 $2$ 次时跳出循环即可。

另外，对于有限小数，我们可以把它看成循环节是 $0$ 的无限循环小数。对此，只要判断余数 $0$ 是否出现了两次即可。

下面是代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int mxn = 1e5+5;
int a,b,c,d,cnt;
bool ap[mxn];
int main(){
	scanf("%d%d%d",&a,&b,&c);
	a%=b;  //去除整数部分
	cnt=1;  //当前小数位数为1
	while(1){  //循环模拟除法
		a*=10;
		d=a/b;   //算小数部分
		a%=b;   //取余数
		if(d==c){  //找到第一个出现的位置，直接输出
			printf("%d",cnt);
			return 0;
		}
		if(ap[a])  //余数出现两次，有循环节，跳出
			break;
		ap[a]=true;
		cnt++;   //增加小数位数
	}
	printf("-1");  //未找到解
	return 0;
}
```


---

## 作者：FP·荷兰猪 (赞：3)

a/b化为最简a′/b′后，我们模拟除法列竖式求答案的过程。由于列竖式的过程中余下的数总比b'小，所以最多b'个不同余数，列竖式的过程中一旦出现相同的余数则是进入了循环。所以我们最多做b'次除法就能求出c是否存在于该分数小数点后以及c的位置。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int gcd(int a,int b)
{
    int c;
    while(b)
    {
        c=a%b;
        a=b;
        b=c;
    }
    return a;
}
int main()
{
    int a,b,c,d,e,i;
    cin>>a>>b>>c;
    d=gcd(a,b);
    a/=d;
    b/=d;
    d=a/b;
    a-=d*b;
    a*=10;
    for(i=1;i<=100000;i++)
    {
        d=a/b;
        a-=d*b;
        if(d==c)
            break;
        a*=10;
    }
    if(i>100000)
        cout<<"-1"<<endl;
    else
        cout<<i<<endl;
    return 0;
}
```

---

## 作者：ChenJr (赞：2)

	题面描述：给你三个整数 a,b,c. 问a除以b所得到的浮点数中小数位内是否包含数字c。
    最开始拿到题目的时候，看到这是浮点数的处理，个人觉得如果采用double相除获取小数点后的位数可能会产生精度上的问题。因此就用了Java里面的BigDecimal进行高精度的处理。

附上骚骚的Java代码    
```java
import java.util.*;
import java.math.*;
public class Main {
	public static void main(String[] args) {
		Scanner sca=new Scanner(System.in);//读入
		BigDecimal res=BigDecimal.valueOf(1);//设置高精度数res的初值为1
		BigDecimal a,b;
		//读入高精度数a、b
		a=sca.nextBigDecimal();
		b=sca.nextBigDecimal();
		int n;
		n=sca.nextInt();
		res=a.divide(b,100005,RoundingMode.HALF_UP); //计算出a/b的结果，并保留100005位小数（为了防止误差）
		String str;//定义字符串
		str=res.toString();//将高精度数res转化为字符串类型。
		int index=str.indexOf('.');//获取转化后的字符串中小数点的位置
		int flag=1;//标记
		for(int i=index;i<str.length()-1;i++) {//枚举
			char tmp;
			tmp=str.charAt(i);//获取当前位的字符
			if(tmp==(n+'0')) {//如果等于n
				System.out.println(i-1);//输出
				flag=0;//标记位0
				break;
			}
		}
		if(flag==1) System.out.println(-1);//如果标记位1，则输出-1
	}
}

```

----------

	后来看到各路大牛的代码，发现其实可以直接模拟就可以了。具体就是每次把a的数扩大10倍，然后再整除b获取下一位的位数，再a%b消除这一位的影响。不断模拟即可。
    代码如下
  

```cpp
#include <bits/stdc++.h>
#define maxn 500
using namespace std;
int main()
{
    int a,b,c;
    cin>>a>>b>>c;//获取三个数
    bool flag=true;//标记
    for(int i=1;i<=maxn;i++){//枚举位数（样例的最大精度再250左右）
        a*=10;//将a先扩大10倍
        if(a/b==c){//用a整除b判断该位是否为c
            cout<<i<<endl;//如果是则输出答案并标记
            flag=false;
            break;
        }
        a=a%b;//将这一位的影响消除
    }
    if(flag) puts("-1");//否则则输出-1
}

```

---

## 作者：zmza (赞：1)

题目要求$c$出现在$b$分之$a$的小数点中的哪一位。
 
这题就是纯模拟，不需要用小数，直接每次乘10就可以了。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int x,y,z;
    scanf("%d%d%d",&x,&y,&z);//输入三个数
    bool flag=1;//标记，如果标记没变就输出-1
    for(int i=1;i<=260;i++){//枚举位数（样例的最大精度再250左右）
        z*=10;//将a先扩大10倍
        if(x/y==z){//用a整除b判断该位是否为c
            printf("%d\n",i);//如果是则输出答案并标记
            flag=0;//有答案了，就不用输出-1了
            break;
        }
        x=x%y;//将这一位的影响消除
    }
    if(flag) printf("-1\n");//否则则输出-1
}
```

---

## 作者：Siteyava_145 (赞：1)

[传送门](luogu.com.cn/problem/CF900B) 不知道为什么我发的CF题解都是B题的

- 题目内容不多赘述。

- （思路）**大模拟**。

   先将 $a/b$ 的整数部分消去，再用无限循环进行模拟，如果遇到某一位相同，就输出这一位；如果余数与之前的某一位的余数相同，那么就说明有循环节，节内没有想要的 $c$。

**The cute code:**
```cpp
#include<bits/stdc++.h>//快乐头文件
using namespace std;
int a,b,c;
int vis[1000005];//标记[12行]余数的出现 
int main(){
	cin>>a>>b>>c;
	a%=b;//把没用的整数搞掉 
	int cnt=1;//小数位数初始化为 1 
	while(true){
		a*=10;
		int x=a/b;//这一位【小数点后第cnt位】 
		a%=b;//余数 
		if(x==c){cout<<cnt;return 0;}//如果那一位符合要求，则输出cnt(小数位数) 
		if(vis[a]>=1)break;//跳出后输出-1 
		vis[a]=1;//标记余数，注意不是上面的 x！！！#3 WA 
		cnt++;//推进 
	}
	cout<<-1;
	return 0;
}
```


---

## 作者：听取MLE声一片 (赞：0)

显然，为了确定 $\dfrac{a}{b}$ 的小数部分，我们要模拟**做竖式除法**的过程。

由于 $a,b$ 都是整数，因此该分数一定是有理数。因此，只要求出循环节，我们就可以得到解。首先我们将这个分数化为最简，然后不断相除，求出余数并记录。一旦发现所求，输出。一旦出现重复的余数，说明出现了循环，只要之前没有发现所求的数字，那么就无解。一旦发现余数为 $0$ ，输出无解。

开一个足够大的数组。模拟高精度除法即可。

下面是代码：

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int a,b,c,d,ans;
bool book[100010];
int main()
{
	a=read(),b=read(),c=read();
	a%=b;
	ans=1;
	while(1){
		a*=10;
		d=a/b;
		a%=b;
		if(d==c){
			printf("%d",ans);
			return 0;
		}
		if(book[a])
			break;
		book[a]=1;
		ans++;
	}
	cout<<-1;
	return 0;
}
```

---

## 作者：Iron_Heart (赞：0)

## 思路

模拟。

模拟竖式除法计算的过程，用 `vis` 数组标记出现过的余数，用 $d$ 表示当前计算到第几位。

如果计算的商为 $c$，输出 $d$ 并退出程序。

如果余数出现过但没有退出程序，说明**出现了循环节**，输出 `-1`。

## 代码

```cpp
#include <cstdio>

bool vis[100100];
int a, b, c;

int main() {
    scanf("%d%d%d", &a, &b, &c);
    for (int d = 1;; ++d) {
        if (vis[a]) {
            break;
        }
        vis[a] = 1;
        a *= 10;
        if ((a / b) == c) {
            printf("%d", d);
            return 0;
        }
        a %= b;
    }
    puts("-1");
    return 0;
}
```


---

