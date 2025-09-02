# 题目信息

# Game of Credit Cards

## 题目描述

After the fourth season Sherlock and Moriary have realized the whole foolishness of the battle between them and decided to continue their competitions in peaceful game of Credit Cards.

Rules of this game are simple: each player bring his favourite $ n $ -digit credit card. Then both players name the digits written on their cards one by one. If two digits are not equal, then the player, whose digit is smaller gets a flick (knock in the forehead usually made with a forefinger) from the other player. For example, if $ n=3 $ , Sherlock's card is $ 123 $ and Moriarty's card has number $ 321 $ , first Sherlock names $ 1 $ and Moriarty names $ 3 $ so Sherlock gets a flick. Then they both digit $ 2 $ so no one gets a flick. Finally, Sherlock names $ 3 $ , while Moriarty names $ 1 $ and gets a flick.

Of course, Sherlock will play honestly naming digits one by one in the order they are given, while Moriary, as a true villain, plans to cheat. He is going to name his digits in some other order (however, he is not going to change the overall number of occurences of each digit). For example, in case above Moriarty could name $ 1 $ , $ 2 $ , $ 3 $ and get no flicks at all, or he can name $ 2 $ , $ 3 $ and $ 1 $ to give Sherlock two flicks.

Your goal is to find out the minimum possible number of flicks Moriarty will get (no one likes flicks) and the maximum possible number of flicks Sherlock can get from Moriarty. Note, that these two goals are different and the optimal result may be obtained by using different strategies.

## 说明/提示

First sample is elaborated in the problem statement. In the second sample, there is no way Moriarty can avoid getting two flicks.

## 样例 #1

### 输入

```
3
123
321
```

### 输出

```
0
2
```

## 样例 #2

### 输入

```
2
88
00
```

### 输出

```
2
0
```

# AI分析结果

### 题目中文重写
# 信用卡游戏

## 题目描述
在第四季之后，夏洛克（Sherlock）和莫里亚蒂（Moriarty）意识到了他们之间争斗的愚蠢，决定通过和平的信用卡游戏来继续他们的较量。

这个游戏的规则很简单：每位玩家拿出自己最喜欢的 $n$ 位信用卡。然后，两位玩家依次说出他们卡片上的数字。如果两个数字不相等，那么数字较小的玩家会被另一个玩家弹一下额头（通常用食指敲击）。例如，如果 $n = 3$，夏洛克的卡片数字是 $123$，莫里亚蒂的卡片数字是 $321$，首先夏洛克说出 $1$，莫里亚蒂说出 $3$，所以夏洛克被弹一下。接着他们都说出 $2$，所以没有人被弹。最后，夏洛克说出 $3$，而莫里亚蒂说出 $1$，莫里亚蒂被弹一下。

当然，夏洛克会诚实地按照卡片上数字的顺序依次说出，而莫里亚蒂作为真正的反派，计划作弊。他打算以其他顺序说出他的数字（不过，他不会改变每个数字出现的总次数）。例如，在上述情况下，莫里亚蒂可以说出 $1$、$2$、$3$，这样他就完全不会被弹，或者他可以说出 $2$、$3$、$1$，让夏洛克被弹两下。

你的目标是找出莫里亚蒂最少可能被弹的次数（没有人喜欢被弹）以及夏洛克最多可能被莫里亚蒂弹的次数。请注意，这两个目标是不同的，并且可能需要使用不同的策略来获得最优结果。

## 说明/提示
第一个样例在题目描述中已经详细说明。在第二个样例中，莫里亚蒂无论如何都无法避免被弹两下。

## 样例 #1
### 输入
```
3
123
321
```
### 输出
```
0
2
```

## 样例 #2
### 输入
```
2
88
00
```
### 输出
```
2
0
```

### 算法分类
贪心

### 综合分析与结论
这些题解主要围绕贪心算法来解决问题，核心思路是通过对两人的信用卡数字进行排序，然后根据不同的比较规则来计算莫里亚蒂最少被弹次数和夏洛克最多被弹次数。部分题解还使用了二分图匹配的方法，但相对复杂。各题解的主要区别在于实现细节和数据处理方式，如使用数组、桶或二分图来存储和比较数字。

### 所选题解
- **作者：QwQcOrZ（4星）**
    - **关键亮点**：思路清晰，使用桶来存储莫里亚蒂的数字，通过贪心策略分别处理两个问题，代码结构简洁。
- **作者：珅肐（4星）**
    - **关键亮点**：明确指出贪心策略的核心思想，结合“田忌赛马”的故事进行解释，代码实现简洁高效。
- **作者：封禁用户（4星）**
    - **关键亮点**：直接阐述贪心思路，通过排序和双指针的方式进行比较，代码逻辑清晰。

### 重点代码
#### QwQcOrZ 的题解
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,temp['9'+1],s['9'+1];
string a,b;

int main()
{
    scanf("%d\n",&n);
    cin>>a>>b;
    a=" "+a;
    b=" "+b;
    int ans=n;
    for (int i=1;i<=n;i++) s[b[i]]++,temp[b[i]]++;
    for (int i=1;i<=n;i++)
    {
    	bool t=0;
    	for (char j=a[i];j<='9';j++) if (s[j]) //从a[i]开始
    	{
    		t=1;
    		s[j]--;
    		ans--;
    		break;
        }
        if (t) continue;
    	for (char j='0';j<='9';j++) if (s[j])
    	{
    		s[j]--;
    		break;
        }
    }
    printf("%d\n",ans);
    ans=0;
    for (int i=1;i<=n;i++)
    {
    	bool t=0;
    	for (char j=a[i]+1;j<='9';j++) if (temp[j]) //从a[i]+1开始，这是两个for最主要的区别
    	{
    		t=1;
    		temp[j]--;
    		ans++;
    		break;
        }
        if (t) continue;
    	for (char j='0';j<='9';j++) if (temp[j])
    	{
    		temp[j]--;
    		break;
        }
    }
    printf("%d\n",ans);

    return 0;
}
```
**核心实现思想**：使用桶存储莫里亚蒂的数字，遍历夏洛克的数字，对于第一个问题，优先选择大于等于当前夏洛克数字的最小数字；对于第二个问题，优先选择大于当前夏洛克数字的最小数字。

#### 珅肐的题解
```cpp
#include<iostream>
#include<cstdio>
#include<ctype.h>
#include<algorithm>
using namespace std;
inline int read(){//快读，可快了，虽然这道题没用
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch))f|=ch=='-',ch=getchar();
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return f?-x:x;
}
char a[1007],b[1007];
int main(){
	int n=read(),j=0,ans=0;//j表示S的当前牌是第几张
	scanf("%s",a),scanf("%s",b);
	sort(a,a+n),sort(b,b+n);//从小到大排序
	for(int i=0;i<n;++i)if(b[i]>=a[j])j++,ans++;//j++表示S出了当前牌，否则S出了他最大的牌
	printf("%d\n",n-ans);j=ans=0;//别忘了清空
	for(int i=0;i<n;++i)if(b[i]>a[j])j++,ans++;//再做一遍
	printf("%d\n",ans);
	return 0;
}
```
**核心实现思想**：对两人的数字进行排序，通过遍历莫里亚蒂的数字，根据比较结果更新夏洛克的指针和答案，分别计算两个问题的结果。

#### 封禁用户的题解
```cpp
#include<bits/stdc++.h>
using namespace std;
#define QAQ 23333
char a[QAQ];
char b[QAQ];
int main(){
	int n;
	scanf("%d",&n);
	scanf("%s%s",a,b);
	sort(a,a+n);
	sort(b,b+n);
	int ans=0;
	int i,j;
	i=j=0;
	while(i<n&&j<n){
		if(b[j]>=a[i]){
			i++;
			j++;
		}
		else{
			j++;
			ans++;
		}
	}
	i=j=0;
	int ans2=0;
	while(i<n&&j<n){
		if(b[j]>a[i]){
			i++;
			j++;
			ans2++;
		} 
		else j++;
	}
	printf("%d\n%d",ans,ans2);
}
```
**核心实现思想**：排序后使用双指针，根据比较结果移动指针并更新答案，分别处理两个问题。

### 最优关键思路或技巧
- **贪心策略**：在处理莫里亚蒂最少被弹次数时，尽量让莫里亚蒂的数字大于等于夏洛克的数字；在处理夏洛克最多被弹次数时，尽量让莫里亚蒂的数字大于夏洛克的数字。
- **排序优化**：对两人的数字进行排序，方便后续的比较和选择。

### 拓展思路
同类型题或类似算法套路：
- 区间调度问题：给定多个区间，选择最多的不重叠区间。
- 活动选择问题：在多个活动中选择最多的不冲突活动。
- 硬币找零问题：用最少的硬币组合出给定的金额。

### 推荐洛谷题目
- P1090 [NOIP2004 提高组] 合并果子
- P1223 排队接水
- P2240 【深基12.例1】部分背包问题

### 个人心得摘录与总结
Lacrymabri 提到自己没想到直接贪心就可以做出来，而是使用了二分图匹配的方法，并且指出直接用匈牙利算法会超时，通过用栈记录访问点来优化。这提示我们在解题时要优先考虑简单直接的算法，同时在使用复杂算法时要注意优化，避免超时。 

---
处理用时：54.11秒