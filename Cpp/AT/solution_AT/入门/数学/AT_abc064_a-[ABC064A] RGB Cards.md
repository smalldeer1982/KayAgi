# [ABC064A] RGB Cards

## 题目描述

AtCoDeer 君有红色、绿色和蓝色三张卡片。  
每张卡片上都写有一个 $1$ 到 $9$ 之间的整数，红色卡片上写着 $r$，绿色卡片上写着 $g$，蓝色卡片上写着 $b$。  
请将这三张卡片按照红、绿、蓝的顺序从左到右排列，读出从左到右的整数，判断这个整数是否是 $4$ 的倍数。

## 说明/提示

### 限制条件

- $1 \leq r, g, b \leq 9$

### 样例解释 1

AtCoDeer 君组成了 $432$，这是 $4$ 的倍数。因此输出 `YES`。

### 样例解释 2

AtCoDeer 君组成了 $234$，这不是 $4$ 的倍数。因此输出 `NO`。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 3 2```

### 输出

```
YES```

## 样例 #2

### 输入

```
2 3 4```

### 输出

```
NO```

# 题解

## 作者：TRZ_2007 (赞：2)

看到C++党大佬的题解，C党的我吓得瑟瑟发抖~~  
~~大家都知道~~：4的倍数特征是末两位能被4整除。所以只要判断$b*10+c$能不能被4整除就行了。  
下面贴代码：
```
#include <stdio.h>
int main()
{
	int a,b,c;//定义a,b,c三个变量（各位大佬也可以用short,long,long long等）
	scanf("%d %d %d",&a,&b,&c);//读入
	if((b*10+c)%4==0) printf("YES");//判断：只要末两位可以被4整除，它本身就可以被4整除
		else printf("NO");//否则就不被4整除
}
```

---

## 作者：chengni (赞：1)

将三个数转换成三位数%4即可


```cpp
#include<bits/stdc++.h>

using namespace std;

int main(){
	int a,b,c;
	cin>>a>>b>>c;
	if((a*100+b*10+c)%4==0) cout<<"YES";
	else cout<<"NO";
	return 0;
} 
```

---

## 作者：李之恒 (赞：0)

来~~water~~一道岛国题

思路很简单，关键是算法的实现。

首先可以用循环读，**边读边做**，顺便用一个变量记录组成的数字大小；

其次判断，可以用**三目运算符**，**比if更快**；

最后就AC了

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int x,tot=0;
	for(int i=1;i<=3;i++)
	{
		scanf("%d",&x);
		tot=tot*10+x;
	}
	tot%4==0?printf("YES\n"):printf("NO\n");
	return 0;
}
```


---

## 作者：minecraft_herobrine (赞：0)

# ~~岛国的题格外的水~~
~~窝~~我的数学告诉~~尼~~你们：2^n的整除特性：只要末n位可以被2^n整除，那这个数也可以。

例如：8(2^3)，需要看末3位、32(2^5) 需要看末5位。

```cpp
#include<bits/stdc++.h>
using namespace std；

int main()
{
	int r,g,b；
	scanf("%d %d %d"，&r，&g，&b)；
	if((g*10+b)%4==0) printf("YES")；
	else printf("NO")；
    return 0；
}
```
## 警告：拒绝COPY，代码内有反COPY字符！

---

