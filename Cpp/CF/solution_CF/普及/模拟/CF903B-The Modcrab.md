# The Modcrab

## 题目描述

沃瓦又在玩一个RPG游戏。在游戏里沃瓦扮演的角色收到了一个任务：去干死一只叫做魔之蟹的大 Boss。

在打了两个小时游戏后沃瓦知道了魔之蟹的各种数值。魔之蟹有 $h_2$ 点生命值和 $a_2$ 点攻击力。沃瓦是个手残，他不想死那么多回，于是就去商店氪了一大堆强力生命回复药剂来准备战斗。

沃瓦的角色有 $h_1$ 点初始生命和 $a_1$ 点攻击力。他还有无限多的强力生命回复药剂，每一瓶都可以给他回复 $c_1$ 点血。沃瓦的每一瓶药剂都是完全一样的。题目数据可以保证 $c_1 > a_2$ 。

战斗包含多个回合。在沃瓦的回合中，它既可以攻击魔之蟹（可以将他的生命值减少 $a_1$ ），也可以喝下一瓶药剂（可将沃瓦的生命值增加 $c_1$ ，沃瓦的生命值值可以超过 $h_1$ ）。现在如果沃瓦和魔之蟹都没有死的话，魔之蟹就会攻击沃瓦，将沃瓦的生命值减少 $a_2$ 。战斗会在沃瓦或魔之蟹中任意一方死亡后结束。

当然，沃瓦想赢，而且他还想赢的越快越好。所以他想制作一个让他用最短时间获胜的策略。

帮帮沃瓦把策略写出来吧！你可以假设沃瓦有无数瓶药水，而且测试数据能保证沃瓦总能赢。

## 样例 #1

### 输入

```
10 6 100
17 5
```

### 输出

```
4
STRIKE
HEAL
STRIKE
STRIKE
```

## 样例 #2

### 输入

```
11 6 100
12 5
```

### 输出

```
2
STRIKE
STRIKE
```

# 题解

## 作者：文·和 (赞：4)

这道题目乍看起来不难。

每个回合判断自己是否会被一招打死，如果会被打死则喝药，否则打一刀BOSS。自己选择完后BOSS会打你 a2 滴血。至于答案，我们不需要模拟两次，模拟出了答案就塞到队列里面，最后输出即可。 

根据以上思路，敲出代码。 

```
#include <bits/stdc++.h>
using namespace std;
int h1,a1,c1,h2,a2; 
queue<int> q;
int main(){
cin>>h1>>a1>>c1;
cin>>h2>>a2;
do{
	if(h1<=a2&&h2>a1) {
		h1+=c1;
		q.push(1);
	}
	else{
	h2-=a1;	
	q.push(2);
	}
	h1-=a2;
}while(h2>0);
cout<<q.size()<<endl;
while(q.size()>0){
	if(q.front()==1) cout<<"HEAL"<<endl;
	else cout<<"STRIKE"<<endl;
	q.pop();
}
return 0;
}
```

但是当你兴奋地提交后，你会发现第三个点就WA了。冥思苦想后你会想起来，如果BOSS已经可以直接干掉了，你还喝药干什么？于是又改了下代码。

以下为AC代码（修改的位置已用星号标记）

```
#include <bits/stdc++.h>
using namespace std;
int h1,a1,c1,h2,a2; //变量
queue<int> q;     //队列q
int main(){
cin>>h1>>a1>>c1;
cin>>h2>>a2;
do{
***	if(h1<=a2&&h2>a1) {   ***   //如果血不够并且无法击杀BOSS
		h1+=c1;      //回血
		q.push(1);    //1为喝药，2为攻击
	}
	else{          //血充足或可以直接击杀BOSS
	h2-=a1;	       //BOSS扣血
	q.push(2);     //塞进队列
	}
	h1-=a2;       //角色扣血
}while(h2>0);     //因为角色肯定能赢所以只要考虑BOSS是否被击杀
cout<<q.size()<<endl;    //答案即为q的长度（因为每次循环q固定增加1）
while(q.size()>0){  
	if(q.front()==1) cout<<"HEAL"<<endl;
	else cout<<"STRIKE"<<endl;
	q.pop();                //输出，不用多说
}
return 0;
}
```

小蒟蒻的题解到此结束，谢谢大家


---

## 作者：zhanghengrui (赞：4)

思路是贪心

对于每一回合，如果Modcrab一次打不死Vova或者Vova能打死Modcrab，Vova就攻击它；否则Vova回血

---

$\mathtt{code}\space\mathsf{(Python3)}$

```python
h1, a1, c1 = map(int, input().split())
h2, a2 = map(int, input().split()) # 读入，变量名和题目中一样
lis = [] # 保存结果用的列表
while h2 > 0: # Modcrab还没死
	if h1 > a2 or a1 >= h2: # Modcrab一次打不死Vova或者Vova能一次打死Modcrab
		h2 -= a1 # Vova攻击
		lis.append('STRIKE')
	else:
		h1 += c1 # Vova回血
		lis.append('HEAL')
	h1 -= a2 # Modcrab攻击
print(len(lis)) # 需要的回合数
print('\n'.join(lis)) # 各回合的操作
```

---

## 作者：hulean (赞：3)

如果它在接下来一回合能一下就将你KO了，那么，你就十分需要回血（一直回到它一下敲不死你），否则你就一直打它就好了。

```cpp
#include<iostream>
using namespace std;
int ans;
int main()
{
    int a1,b1,c1,a2,b2;
    int a1_x,a2_x;
    cin>>a1>>b1>>c1>>a2>>b2;
    a1_x=a1;a2_x=a2;
    while(a1>0&&a2>0)//第一次循环，判断次数
    {
        if(a2<=b1)a2-=b1;
        else if(b2>=a1)a1+=c1;
        else a2-=b1;
        if(a2>0)a1-=b2;
        ans++;
    }
    cout<<ans<<endl;
    while(a1_x>0&&a2_x>0)//第二次循环，求每一步
    {
        if(a2_x<=b1)a2_x-=b1,cout<<"STRIKE\n";
        else if(b2>=a1_x)cout<<"HEAL\n",a1_x+=c1;
        else cout<<"STRIKE\n",a2_x-=b1;
        if(a2_x>0)a1_x-=b2;
    }
    return 0;
}
```

---

## 作者：Histone (赞：2)

思路不难，就是一直打，打不动就嗑回血。

代码实现需要注意的点

- 当沃瓦的攻击力大于大于魔之蟹当前生命值时，**攻击**

- 当沃瓦的生命值小于魔之蟹的攻击力时，**回血**

- 其他情况时，**攻击**

然后将结果存到字符串里即可。

代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
int h1,a1,c,h2,a2,ans;   
string s;
int main(void){
    cin>>h1>>a1>>c;
    cin>>h2>>a2;
    while(h2>0){
    	if(h2<=a1)s+="STRIKE\n",h2-=a1;
        else if(h1<=a2) s+="HEAL\n",h1+=(c-a2);
        else s+="STRIKE\n",h1-=a2,h2-=a1;
        ans++;
    }
    
    cout<<ans<<endl<<s;
    return 0;
}
```

---

## 作者：LCGUO (赞：0)

开始做小模拟题啦٩(๑>◡<๑)۶

---

我们可以在模拟的时候用上贪心的思想。

对于每一次轮到自己的时候，我们有两个选择：**回血**和**攻击**。

对于这两个选择，如果当前我的攻击伤害大于他的总血量时，我可以直接攻击，在我的回合结束游戏，不用管 Boss 的攻击了。

如果当前的血量小于 Boss 的攻击伤害的话我们就必须选择回血，否则游戏将会结束，并且我们打不赢 Boss。

由于保证我们能赢，所以我们没有必要在 Boss 打不死我们的情况下使用回血技能。

然后能打就打，按题意模拟就好了。

---

代码如下：

```cpp
#include<bits/stdc++.h>
#define rint register int
using namespace std;
inline int read(){
    int s=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=0;c=getchar();}
    while(c>='0'&&c<='9')s=(s<<1)+(s<<3)+c-48,c=getchar();
    return f?s:-s;
}
int h_I,a_I,c_I,h_B,a_B;
int rc[100010],num;
int main(){
    h_I=read(); a_I=read(); c_I=read();
    h_B=read(); a_B=read();
    while(h_B>0){
        if(a_I>=h_B){
            rc[++num]=1;
            h_B-=a_I;
        }
        else if(h_I<=a_B){
            rc[++num]=2;
            h_I+=c_I;
        }
        else{
            rc[++num]=1;
            h_B-=a_I;
        }
        h_I-=a_B;
    }
    printf("%d\n",num);
    for(rint i=1;i<=num;++i){
        if(rc[i]==1) puts("STRIKE");
        else puts("HEAL");
    }
    return 0;
}
```

---

## 作者：long_long (赞：0)

这模拟题好水。

# 题目大意：
在打了两个小时游戏后沃瓦知道了魔之蟹的各种数值。魔之蟹有 h2	点生命值和 a2点攻击力。沃瓦是个手残，他不想死那么多回，于是就去商店氪了一大堆强力生命回复药剂来准备战斗。

沃瓦的角色有 h1 点初始生命和 a1	点攻击力。他还有无限多的强力生命回复药剂，每一瓶都可以给他回复 c1 点血。沃瓦的每一瓶药剂都是完全一样的。题目数据可以保证 c1 > a2 	
  。战斗包含多个回合。在沃瓦的回合中，它既可以攻击魔之蟹（可以将他的生命值减少 a1	），也可以喝下一瓶药剂（可将沃瓦的生命值增加 c1 ，沃瓦的生命值值可以超过 h1）。现在如果沃瓦和魔之蟹都没有死的话，魔之蟹就会攻击沃瓦，将沃瓦的生命值减少 a2 。战斗会在沃瓦或魔之蟹中任意一方死亡后结束。
  

# 思路：
现在每局沃瓦有两种操作，回血，或攻击。

**回血：**  沃瓦有无限多瓶回血药，所以每局都可以回血。回的血量为c1。

**攻击：**  沃瓦的攻击力为a1，每局都可以攻击。

那咱们就循环直到boss的血量没了就行了，为什么呢，题里不是说了任意一方死了吗？因为这个模拟考虑的是在沃瓦赢的情况下，然后尽可能快，所以写不写没关系。

咱们循环里有三种情况。

**一：**  当boss的血<=沃瓦的攻击力，这样就攻击，把boss一刀了结了。

**二：**  当沃瓦的血<=boss的攻击力，一定要回血，要不然就完了。

**三：**  当前面两个都不满足，就照常攻击（比如第一轮）。

窝们去康康代码吧~~~~

# 代码：

```
#include<iostream>
using namespace std;
int a[100005];
int main(){
    int a1,a2,c1,h1,h2;
    cin>>h1>>a1>>c1;//输入
    cin>>h2>>a2;//输入
    int sum=0;//累加器
    while(h1>0&&h2>0){//沃瓦的可写可不写
        if(h1<=a2){//若自己的血量<=boss的攻击力
            a[sum]=2;//记为2
            h1+=c1;//操作
            h1-=a2;
            sum++;//累加
        }
        else if(h2<=a1){//若boss的血量<=自己的攻击力
            a[sum]=1;//记为1
            h2-=a1;//操作
            sum++;//累加
            break;//跳出
        }
        else{//否则
            a[sum]=1;//记为1
            h2-=a1;//操作
            h1-=a2;
            sum++;//累加
        }
    }
    cout<<sum<<endl;//输出个数
    for(int i=0;i<=sum;i++){//输出
        if(a[i]==1) cout<<"STRIKE"<<endl;
        else cout<<"HEAL"<<endl;
    }
    return 0;//结束
}
```






---

## 作者：北雪2009 (赞：0)

其实，这道题一点都不难，只要考虑剩余的生命值。   
如果他还能被大魔王揍一次，那就继续揍！直到剩余的生命值一揍回~~屎~~死的时候，就狂补血，直到还能被大魔王揍一次的时候，就继续揍······以此类推。    
	好啦，都讲得差不多了，贴上代码：
   ```cpp
#include<bits/stdc++.h>    //万能头，这，谁都知道
#include<stdio.h>
#include<string>     //输出要用字符串，加上保险
using namespace std;
int h1,a1,c,h2,a2,ans;   
string str;
int main(){
	ios::sync_with_stdio(false);    //cin,cout快读快输，用scanf和printf的同学就不要用了，会RE。
	cin>>h1>>a1>>c;
	cin>>h2>>a2;
	while(h2>0){   //判断大魔王有没有死，如果死了就不执行
		if(h1-a2>0){  //如果能被大魔王揍一次 
			str+="STRIKE\n";
			h1-=a2,h2-=a1;
		}
		else{   //要补血     
			str+="HEAL\n";
			h1+=c;
		}
		ans++;    //记录回合数
	}
	cout<<ans<<'\n'<<str;    //输出
	return 0;   //华丽结束!
}
```


---

