# MUH and Sticks

## 题目描述

Two polar bears Menshykov and Uslada from the St.Petersburg zoo and elephant Horace from the Kiev zoo got six sticks to play with and assess the animals' creativity. Menshykov, Uslada and Horace decided to make either an elephant or a bear from those sticks. They can make an animal from sticks in the following way:

- Four sticks represent the animal's legs, these sticks should have the same length.
- Two remaining sticks represent the animal's head and body. The bear's head stick must be shorter than the body stick. The elephant, however, has a long trunk, so his head stick must be as long as the body stick. Note that there are no limits on the relations between the leg sticks and the head and body sticks.

Your task is to find out which animal can be made from the given stick set. The zoo keeper wants the sticks back after the game, so they must never be broken, even bears understand it.

## 说明/提示

If you're out of creative ideas, see instructions below which show how to make a bear and an elephant in the first two samples. The stick of length 2 is in red, the sticks of length 4 are in green, the sticks of length 5 are in blue.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF471A/a55b02778d08bde8867cd5aaa95268e697371d67.png)

## 样例 #1

### 输入

```
4 2 5 4 4 4
```

### 输出

```
Bear```

## 样例 #2

### 输入

```
4 4 5 4 4 5
```

### 输出

```
Elephant```

## 样例 #3

### 输入

```
1 2 3 4 5 6
```

### 输出

```
Alien```

# 题解

## 作者：Arghariza (赞：2)

**~~直 接 % 你~~**

要找到数列里是否有 $4$ 个数相等，最懒的方法是全部从小到大排序一遍，然后遍历 $i=[1,\,n-3]$ ，意思是找以 $i$ 为开头的连续 $4$ 个数是否相同。

如果找到了 $4$ 个数全部相等，有一个非常懒的做法：把 $4$ 个数都赋值为 $0$ ，然后再从大到小排序。排完后直接判断 $s_1,s_2$ 是否相同即可。

如果没找到呢？我们每轮 $i$ 定义一个 $f$，初始值为 $1$ 表示假设当前 $4$ 个数全部相等，而当我们发现矛盾的时候 $f$ 再赋值为 $0$ 。如果最后 $f$ 仍然为 $1$ ，直接赋值 $4$ 个数然后 $break$ ，否则继续。

具体就差不多是这些了，代码里面有注释：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n = 6, flag, s[10];// flag用来判断是否有4个数相同

signed main() {
	for (int i = 1; i <= n; i++) cin >> s[i];// 输入
	sort(s + 1, s + n + 1);// 从小到大排序
	for (int i = 1; i <= n - 3; i++) {// 枚举每个起点
		int f = 1;// 初始化f
		for (int j = i + 1; j <= i + 3; j++) {// 枚举当前4个点
			if (s[j] != s[j - 1]) f = 0;// 如果出现矛盾，即相邻2个不同就令f为0
		}
		if (f) {// 如果4个数相等
			flag = 1;// 得到答案（Bear或者Elephant）
			for (int j = i; j <= i + 3; j++) {// 全部都赋值为0
				s[j] = 0;
			}
			break;
		}
	}
	sort(s + 1, s + n + 1, greater<int> ());//从大到小排序，之前相同4个数全部过滤掉。
	if (flag == 1) {// 如果有4个数相同
		if (s[1] != s[2]) cout << "Bear";// 如果前两个相同
		else cout << "Elephant";// 否则
	} else cout << "Alien";// 否则
	return 0;
}
```

---

## 作者：fzj2007 (赞：1)

## 本蒟蒻又来了~~~

最近一直在做 $CF$ 黄题 ~~（别的不会......）~~。

好了废话不多说，开始看题。

------------

# 第一步 读题

我真想次了这个翻译人.......

> 给出6个数，如果相同的数字数量小于4个，就输出"Allen",否则比较剩下两个数，如果剩下两个数相等，输出"Elephant",否则输出"bear".(字符串都不加引号）。

给出6个数，如果相同的数字数量小于4个，就输出"Allen",否则**比较剩下两个数**。

~~加黑的部分，谁告诉你一定是剩下两个数了。。~~**好吧我们姑且认为如果有5个数相同，那么前4个算作一组，然后比较剩下一个和最后一个。**

这同时也是这个题目的坑点！

# 第二步 寻找思路

看清题目了，我们来找找思路。

我们发现他只给出 $6$ 个数而不是 $n$ 个，我们就可以从这里入手。我们先读入这六个数，**然后排序**，如果要有 $4$ 个数相同的话，那么排完序的数组中一定有 **第一个与第四个相等或第二个与第五个相等或第三个与第六个相等。** 为什么呢？因为我们已经进行排序了，如果第一个与第四个相等，那么第一个、第二个、第三个、第四个一定都相等。第二个与第五个相等、第三个与第六个相等是同理的。

**以上是判断是否有四个数及以上相等的思路。下面看判断后两个数：**

因为一定有四个数相等，所以我们可以直接暴力寻找另外两个数在哪里，然后直接判断（因为一共只有 $6$ 个数，所以只需要进行三次判断）。下面还是看这里的代码吧。。

```
if(a[1]==a[4]&&a[5]==a[6]||a[2]==a[5]&&a[1]==a[6]||a[3]==a[6]&&a[1]==a[2]){
	//这里输出
}
```
现在一共有三种情况，分析完两种了，最后直接输出`Bear`就可以了。

# 第三步 其他

大家会快读吗？

---------
如果想了解，可以在[洛谷日 ~~（爆）~~ 报](https://www.luogu.com.cn/blog/encore/io-you-hua-nei-suo-shi)里查看，这里不再赘述。

# 第四步 代码

~~终于到了你们最喜欢的代码环节了~~。

### 温馨提示：请勿抄袭，后果自负~

```
#include<bits/stdc++.h>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
namespace IN{
    const int MAX_INPUT = 1000000;
    #define getc() (p1==p2&&(p2=(p1=buf)+inbuf->sgetn(buf,MAX_INPUT),p1==p2)?EOF:*p1++)
    char buf[MAX_INPUT],*p1,*p2;
    template<typename T>inline bool read(T &x) {
        static std::streambuf *inbuf=cin.rdbuf();
        x=0;
        register int f=0,flag=false;
        register char ch=getc();
        while(!isdigit(ch)){
            if (ch=='-') f=1;
        	ch=getc();
        }
        if(isdigit(ch)) x=x*10+ch-'0',ch=getc(),flag=true;
        while(isdigit(ch)) {
            x=x*10+ch-48;
            ch=getc();
        }
        x=f?-x:x;
        return flag;
    }
    template<typename T,typename ...Args>inline bool read(T& a,Args& ...args) {
       return read(a)&&read(args...);
    }
    #undef getc
}

namespace OUT{
    template<typename T>inline void put(T x){
        static std::streambuf *outbuf=cout.rdbuf();
        static char stack[21];
        static int top=0;
        if(x<0){
            outbuf->sputc('-');
            x=-x;
        }
        if(!x){
            outbuf->sputc('0');
            outbuf->sputc('\n');
            return;
        }
        while(x){
            stack[++top]=x%10+'0';
            x/=10;
        }
        while(top){
            outbuf->sputc(stack[top]);
            --top;
        }
        outbuf->sputc('\n');
    }
    inline void putc(const char ch){
        static std::streambuf *outbuf=cout.rdbuf();
        outbuf->sputc(ch);
    }
    inline void putstr(string s){
    	for(register int i=0;i<s.length();i++) putc(s[i]);
	}
    template<typename T>inline void put(const char ch,T x){
        static std::streambuf *outbuf=cout.rdbuf();
        static char stack[21];
        static int top = 0;
        if(x<0){
            outbuf->sputc('-');
            x=-x;
        }
        if(!x){
            outbuf->sputc('0');
            outbuf->sputc(ch);
            return;
        }
        while(x){
            stack[++top]=x%10+'0';
            x/=10;
        }
        while(top){
            outbuf->sputc(stack[top]);
            --top;
        }
        outbuf->sputc(ch);
    }
    template<typename T,typename ...Args> inline void put(T a,Args ...args){
        put(a);put(args...);
    }
    template<typename T,typename ...Args> inline void put(const char ch,T a,Args ...args){
        put(ch,a);put(ch,args...);
    }
}
using IN::read;
using OUT::putc;
using OUT::putstr;
int a[6];
int main(){
	read(a[1],a[2],a[3],a[4],a[5],a[6]);//读入
	sort(a+1,a+7);//排序
	if(a[1]!=a[4]&&a[2]!=a[5]&&a[3]!=a[6]){//直接判断
		putstr("Alien\n");
		return 0;
	}
	if(a[1]==a[4]&&a[5]==a[6]||a[2]==a[5]&&a[1]==a[6]||a[3]==a[6]&&a[1]==a[2]){//判断Elephant
		putstr("Elephant\n");
		return 0;
	}
	putstr("Bear\n");//最后输出
	return 0;
}
```

这里有三个彩蛋......

本题[AC&最快时间](https://www.luogu.com.cn/record/32651547)记录。

# 第五步 宣传

如果有帮助，请点个赞，谢谢！（这篇题解写了300行呢......）

[我的主页](https://www.luogu.com.cn/user/172370)和[博客](https://www.luogu.com.cn/blog/fzj2007/)，欢迎关注！



---

## 作者：TheShuMo (赞：0)

## 题意简述

给定 $6$ 个数 $a_1,a_2,a_3,a_4,a_5,a_6$，如果里面仅有少于 $4$ 个数相等，那么输出"Alien"。

如果里面有至少 $4$ 个数相等，剩下两个数若相等，则输出"Elephant"，否则输出"Bear"。

~~话说翻译里Alien打错了，大小写也没改~~

## 思路

输入进来，利用桶排的思想，把数据存桶与数组，最后遍历一遍桶，若有桶内元素数量大于等于 $4$ 的，则在数组中数出四个与该数相等的，标记为 $+\infty$，然后排序一遍数组，判断前两个数即可。。

## 代码
~~~cpp
#include<bits/stdc++.h>
using namespace std;
int a[100001],c[7];
void sol(int n){
	int k=0;
	for(int i=1;i<7;i++)if(c[i]==n&&k<4)c[i]=0x3f3f3f3f,k++;//只标记4个
	sort(c+1,c+1+6);
	if(c[1]==c[2])cout<<"Elephant";
	else cout<<"Bear";
	return;
}
int main(){
	int tp;
	for(int i=1;i<=6;i++){
		cin>>tp;
		a[tp]++;c[i]=tp;
	}
	for(int i=1;i<100001;i++){
		if(a[i]>=4){
			sol(i);
			return 0;
		}
	}
	cout<<"Alien";
}
~~~


---

## 作者：zeekliu (赞：0)

由于数据量非常小，直接采用 ```if``` 和 ```else``` 嵌套判断情况。

**详情看代码注释（~~这里不方便解释~~）：**

```cpp
//CF471A 22-08-20
#include <bits/stdc++.h>
using namespace std;

int main() 
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0); // cin,cout 加速
	int a[7],f=0; // f 用来记录状态
	for (int i=1;i<=6;i++) cin>>a[i];
	sort(a+1,a+7); // 排序，使得要统计的情况减少至 3 种，较为方便
	if (a[1]==a[2] && a[2]==a[3] && a[3]==a[4]) f=1; // f=1 时表示下标 1-4 元素相等
	else if (a[2]==a[3] && a[3]==a[4] && a[4]==a[5]) f=2; // f=2 时表示下标 2-5 元素相等
	else if (a[3]==a[4] && a[4]==a[5] && a[5]==a[6]) f=3; // f=3 时表示下标 3-6 元素相等
	if (f==0) cout<<"Alien"<<endl; // 都不满足，说明没有 4 个相同的元素，输出 Alien
	else 
	{ // 剩余两个元素判断是否相等
		if (f==1 && a[5]==a[6]) cout<<"Elephant"<<endl; 
		else if (f==2 && a[1]==a[6]) cout<<"Elephant"<<endl;
		else if (f==3 && a[1]==a[2]) cout<<"Elephant"<<endl;
		else cout<<"Bear"<<endl; // 不相等时输出 Bear
	}
	return 0;
}
```

看懂了吧～

补充一句：原题题面上 ```Alien``` 错拼为 ```Allen```，请管理看到这篇题解后一并改正。

---

## 作者：晨·曦 (赞：0)

### - 思路
- 先用数组读入存数字，再用**四重循环**找到四个相同的数，并标记为 `0`，然后判断剩下的两个数是否相同即可。
- 只有六个数字要用来循环，再加上一点优化（其实没什么必要），四层循环也不会太慢。

### - 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10],p[6];
bool b;
int main() {
	for(int i=1; i<=6; i++) cin>>a[i]; //输入
    //循环找4个相同的数
	for(int i=1; i<=3; i++) {
		for(int j=i+1; j<=4; j++) {
			for(int k=j+1; k<=5; k++) {
				for(int l=k+1; l<=6; l++) {
					if(a[i]==a[j]&&a[j]==a[k]&&a[k]==a[l]) {
						a[i]=0; //标记为0
						a[j]=0;
						a[k]=0;
						a[l]=0;
						b=1; // 记录有没有4个相同的数
						break; //退出循环
					}
				}
				if(b) break; 
			}
			if(b) break;
		}
		if(b) break;
	}
	int q=0;
	if(b) {
		for(int i=1; i<=6; i++) if(a[i]) p[++q]=a[i]; //找剩下两个数
        // 输出
		if(p[1]==p[2]) cout<<"Elephant";
		else cout<<"Bear";
	} else cout<<"Alien";

	return 0;
}
```


---

## 作者：_Legacy (赞：0)

#### 分析

我们统计得到的每个数字的数量，方便后面的计算：

```
	int a[6][2]={0},len=0,x,t;
	//用a来统计，[i][0]部分是个数，[i][1]部分是数字
	for(int i=0;i<6;i++){//总共六个数
		cin >> x;
		t=1;
		for(int j=0;j<len;j++){
			if(a[j][1]==x){
				a[j][0]++;
				t=0;
			} 
		}//这个数要是已被统计，那么个数增加
		if(t){
			a[len][1]=x,a[len][0]++;
			len++;
		}//如果没有被统计，那么统计得到的数字增加
	}
```

现在来看看判断部分：

情况为"Bear"时可以是

1. 两个不同的数字在前，相同的四个数字在后。
2. 一个不同的数字在前，一个在后，相同的四个数字在中间。
3. 两个不同的数字在后，相同的四个数字在前。

所以统计数组可以是:
```
1 1 4 0 0 0
1 4 1 0 0 0
4 1 1 0 0 0
```
可见，如果情况是"Bear"，前三中一定有个4。

情况为"Elephant"时可以是

1. 两个相同的在前，四个相同的在后。
2. 与1.相反。
3. 剩下两个正好和前四个相同(都一样)。

```
2 4 0 0 0 0
4 2 0 0 0 0
6 0 0 0 0 0
```
可见，如果情况为"Elephant"必定和举例一样。

其它的情况就是"Allen"。



------------

#### 上代码

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a[6][2]={0},len=0,x,t;
	for(int i=0;i<6;i++){
		cin >> x;
		t=1;
		for(int j=0;j<len;j++){
			if(a[j][1]==x){
				a[j][0]++;
				t=0;
			} 
		}
		if(t){
			a[len][1]=x,a[len][0]++;
			len++;
		}	
	}
	if((a[0][0]==4&&a[1][0]==2)||(a[1][0]==4&&a[0][0]==2)||a[0][0]==6)
		cout << "Elephant" << endl;
	else{
		if(a[0][0]>=4||a[1][0]>=4||a[2][0]>=4) 
			cout << "Bear" << endl;
		else
			cout << "Alien" << endl; 
	}		
}
//CF471
```

---

## 作者：MrFish (赞：0)

整体思路：把数组排序，计算最多有多少重复的数字，并记录有多少个数在数组中出现了两次以上。如果重复的数字小于4，那么是Alien，如果重复的数字大于4，并且出现两次以上的数的个数大于等于2，或重复的数字个数为6（因为这时两次以上的数的个数为一，但也可以拼成Elephant），输出Elephant，否则输出Bear。

AC Code：

```cpp
#include<iostream>
#include<algorithm>
#include<cmath>

using namespace std;

int main()
{
    int a[7];
    int same=1;
    int maxs=-1;
    int s2=0;
    for(int i=0;i<6;i++)
    {
        cin>>a[i];
    }  //读入
    sort(a,a+6);  //排序
    for(int i=0;i<5;i++)
    {
        if(a[i]==a[i+1])  //如果相等
        {
            same++;
            maxs=max(same,maxs);
            if(same==2)  //统计有多少个数在数组中出现了两次以上
            {
                s2++;
            }
        }
        else
        {
            same=1;
        }
    }
    if(maxs<4)  //如果重复的数字小于4
    {
        cout<<"Alien";
    }
    else
    {   
        if(s2>=2||maxs==6)  //出现两次以上的数的个数大于等于2，或重复的数字个数为6
        {
            cout<<"Elephant";
        }
        else
        {
            cout<<"Bear";
        }
    }
    
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

这道题只需要模拟题目的意思就行了。还是不算太难的（虽然是个黄题）。

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a[7],ans;
	for(int i=1;i<=6;i++) cin>>a[i];
	sort(a+1,a+7);//方便讨论
	if((a[1]= =a[2]&&a[2]==a[3]&&a[3]==a[4]&&a[5]!=a[6])||(a[2]==a[3]&&a[3]==a[4]&&a[4]==a[5]&&a[1]!=a[6])||(a[3]==a[4]&&a[4]==a[5]&&a[5]==a[6]&&a[1]!=a[2])) cout<<"Bear"<<endl;//判断能否拼成熊
	else if((a[1]==a[2]&&a[2]==a[3]&&a[3]==a[4]&&a[5]==a[6])||(a[3]==a[4]&&a[4]==a[5]&&a[5]==a[6]&&a[1]==a[2])) cout<<"Elephant"<<endl;//大象
	else cout<<"Alien"<<endl;
 } 
```

---

