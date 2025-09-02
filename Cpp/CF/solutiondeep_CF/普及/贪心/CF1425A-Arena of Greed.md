# 题目信息

# Arena of Greed

## 题目描述

Lately, Mr. Chanek frequently plays the game Arena of Greed. As the name implies, the game's goal is to find the greediest of them all, who will then be crowned king of Compfestnesia.

The game is played by two people taking turns, where Mr. Chanek takes the first turn. Initially, there is a treasure chest containing $ N $ gold coins. The game ends if there are no more gold coins in the chest. In each turn, the players can make one of the following moves:

- Take one gold coin from the chest.
- Take half of the gold coins on the chest. This move is only available if the number of coins in the chest is even.

Both players will try to maximize the number of coins they have. Mr. Chanek asks your help to find the maximum number of coins he can get at the end of the game if both he and the opponent plays optimally.

## 说明/提示

For the first case, the game is as follows:

1. Mr. Chanek takes one coin.
2. The opponent takes two coins.
3. Mr. Chanek takes one coin.
4. The opponent takes one coin.

For the second case, the game is as follows:

1. Mr. Chanek takes three coins.
2. The opponent takes one coin.
3. Mr. Chanek takes one coin.
4. The opponent takes one coin.

## 样例 #1

### 输入

```
2
5
6```

### 输出

```
2
4```

# AI分析结果

### 题目内容重写
#### 题目描述
最近，Mr. Chanek 经常玩一款名为“贪婪竞技场”的游戏。顾名思义，游戏的目标是找出最贪婪的人，他将成为 Compfestnesia 的国王。

游戏由两个人轮流进行，Mr. Chanek 先手。初始时，宝箱中有 $N$ 枚金币。当宝箱中没有金币时，游戏结束。每回合，玩家可以执行以下两种操作之一：

- 从宝箱中取出一枚金币。
- 取走宝箱中一半的金币。此操作仅在宝箱中金币数为偶数时可用。

双方都会尽力最大化自己获得的金币数。Mr. Chanek 请你帮助他计算，如果双方都采取最优策略，游戏结束时他最多能获得多少金币。

#### 说明/提示
对于第一个样例，游戏过程如下：

1. Mr. Chanek 取一枚金币。
2. 对手取两枚金币。
3. Mr. Chanek 取一枚金币。
4. 对手取一枚金币。

对于第二个样例，游戏过程如下：

1. Mr. Chanek 取三枚金币。
2. 对手取一枚金币。
3. Mr. Chanek 取一枚金币。
4. 对手取一枚金币。

#### 样例 #1
##### 输入
```
2
5
6
```

##### 输出
```
2
4
```

### 题解分析与结论
#### 综合分析
该问题的核心在于双方都采取最优策略时，先手（Mr. Chanek）能获得的最大金币数。题解中主要采用了贪心策略，结合特判来处理某些特殊情况（如 $n=4$ 时）。难点在于如何确保在每一步操作中，先手能够最大化自己的收益，同时限制对手的收益。

#### 最优关键思路
1. **贪心策略**：优先选择能最大化当前收益的操作，但需要结合后续步骤的收益来调整策略。
2. **特判处理**：对于某些特殊情况（如 $n=4$），需要单独处理，以确保最优解。
3. **动态调整**：根据当前剩余金币数的奇偶性，动态调整策略，确保对手无法在后续步骤中获得较大收益。

#### 推荐题目
1. [P1880 石子合并](https://www.luogu.com.cn/problem/P1880)
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)

### 所选高分题解
#### 题解1：作者：honey_ (赞：3)
##### 星级：4星
##### 关键亮点
- **贪心策略**：优先选择取一半金币，但结合特判处理 $n=4$ 的情况。
- **代码简洁**：通过简单的循环和条件判断实现，代码可读性高。

##### 核心代码
```cpp
int solve()
{
	int n,ret=0,now=1;
	scanf("%lld",&n);
	while(n>0)
	{
		int cnt=0;
		if(n%2==0 && n>>1&1)
		    n>>=1,cnt=n;
		else if(n==4)
		    cnt=3,n-=3;
		else
		    cnt=1,n--;
		ret+=cnt*now;
		now^=1;
	}
	return ret;
}
```

#### 题解2：作者：kon_tori (赞：2)
##### 星级：4星
##### 关键亮点
- **详细分析**：对每一步操作进行了详细分析，确保最优策略。
- **特判处理**：特别处理了 $n=4$ 的情况，确保最优解。

##### 核心代码
```cpp
int main(){
    /*cin>>T;*/read(T);
    while(T--){//T组数据
        ans1=0;
        //ans2=0;每次清零A，B持有的硬币数
        /*cin>>n;*/read(n);
        while(1){
            if(n==1){
                ans1++;
                goto sp;
            }//只剩下1枚硬币可提前结束
            if(n==4){
                ans1+=3;
                //ans2++;
                goto sp;
            }//特判剩下4枚硬币的情况
            if( n%4==0 || n%2==1 ){
                n--;
                ans1++;
                goto sp1;
            }
            if( n%2==0 && n%4!=0 ){
                n/=2;
                ans1+=n;
                goto sp1;
            }//A的回合
            sp1 : ;
            if(n==1){
                //ans2++;
                goto sp;
            }//只剩下1枚硬币可提前结束
            if(n==4){
                ans1++;
                //ans2+=3;
                goto sp;
            }//特判剩下4枚硬币的情况
            if( n%4==0 || n%2==1 ){
                n--;
                //ans2++;
                goto sp2;
            }
            if( n%2==0 && n%4!=0 ){
                n/=2;
                //ans2+=n;
                goto sp2;
            }//B的回合
            sp2 : ;
        }
        sp : ;
        cout<<ans1<<"\n";//输出最后A持有的硬币数
    }
    return 0;
}
```

#### 题解3：作者：帝千秋丶梦尘 (赞：1)
##### 星级：4星
##### 关键亮点
- **深入分析**：通过具体例子（如 $n=12$）深入分析了最优策略。
- **特判处理**：特别处理了 $n=4$ 的情况，确保最优解。

##### 核心代码
```cpp
signed main(void)
{
	std::ios::sync_with_stdio(false);
	cin>>T;
	while(T--)
	{
		cin>>x;
		ans=0,flag=0;
		while(x)
		{
			if(!flag)
			{
				flag=1;
				if(x%2==1)
				{
					ans++;
					x--;
				}
				else{
					if((x/2)%2==0&&x!=4)
					{
						ans++;
						x--;
					}
					else{
						ans+=x/2;
						x-=x/2;
					}
				}
			}
			else{
				flag=0;
				if(x%2==1)
				{
					x--;
				}
				else{
					if((x/2)%2==0&&x!=4)
					{
						x--;
					}
					else{
						x-=x/2;
					}
				}
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

### 个人心得总结
- **调试经历**：部分题解作者在初期采用了简单的贪心策略，但发现无法通过所有测试用例，随后通过深入分析和特判处理，最终找到了最优解。
- **顿悟感想**：在处理博弈类问题时，不能仅仅考虑当前的最大收益，还需要考虑对手的后续操作，确保全局最优。

---
处理用时：51.23秒