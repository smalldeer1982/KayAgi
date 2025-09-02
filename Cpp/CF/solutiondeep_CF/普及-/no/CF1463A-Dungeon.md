# 题目信息

# Dungeon

## 题目描述

You are playing a new computer game in which you have to fight monsters. In a dungeon you are trying to clear, you met three monsters; the first of them has $ a $ health points, the second has $ b $ health points, and the third has $ c $ .

To kill the monsters, you can use a cannon that, when fired, deals $ 1 $ damage to the selected monster. Every $ 7 $ -th (i. e. shots with numbers $ 7 $ , $ 14 $ , $ 21 $ etc.) cannon shot is enhanced and deals $ 1 $ damage to all monsters, not just one of them. If some monster's current amount of health points is $ 0 $ , it can't be targeted by a regular shot and does not receive damage from an enhanced shot.

You want to pass the dungeon beautifully, i. e., kill all the monsters with the same enhanced shot (i. e. after some enhanced shot, the health points of each of the monsters should become equal to $ 0 $ for the first time). Each shot must hit a monster, i. e. each shot deals damage to at least one monster.

## 说明/提示

In the first test case, you can do as follows: $ 1 $ -th shot to the first monster, $ 2 $ -th shot to the second monster, $ 3 $ -th shot to the third monster, $ 4 $ -th shot to the first monster, $ 5 $ -th shot to the third monster, $ 6 $ -th shot to the third monster, and $ 7 $ -th enhanced shot will kill all the monsters.

In the second test case, you can't kill monsters with the same enhanced shot, because the total number of health points of monsters is $ 3 $ , and you will kill them in the first 3 shots.

## 样例 #1

### 输入

```
3
3 2 4
1 1 1
10 1 7```

### 输出

```
YES
NO
NO```

# AI分析结果

### 题目内容
# 地下城

## 题目描述
你正在玩一款新的电脑游戏，在游戏中你需要与怪物战斗。在你试图通关的一个地下城中，你遇到了三只怪物；第一只怪物有 $a$ 点生命值，第二只怪物有 $b$ 点生命值，第三只怪物有 $c$ 点生命值。

为了杀死这些怪物，你可以使用一门大炮，每次开炮会对选定的怪物造成 $1$ 点伤害。每第 $7$ 次（即射击次数为 $7$、$14$、$21$ 等等）开炮是强化射击，会对所有怪物造成 $1$ 点伤害，而不仅仅是其中一只。如果某个怪物当前的生命值为 $0$，它就不能被普通射击选中，也不会从强化射击中受到伤害。

你希望漂亮地通关地下城，也就是说，用同一次强化射击杀死所有怪物（即在某次强化射击之后，每只怪物的生命值首次同时变为 $0$）。每次射击都必须命中怪物，即每次射击至少对一只怪物造成伤害。

## 说明/提示
在第一个测试用例中，你可以这样做：第 $1$ 次射击打第一只怪物，第 $2$ 次射击打第二只怪物，第 $3$ 次射击打第三只怪物，第 $4$ 次射击打第一只怪物，第 $5$ 次射击打第三只怪物，第 $6$ 次射击打第三只怪物，第 $7$ 次强化射击将杀死所有怪物。

在第二个测试用例中，你不能用同一次强化射击杀死怪物，因为怪物的总生命值为 $3$，你会在前 $3$ 次射击中就杀死它们。

## 样例 #1
### 输入
```
3
3 2 4
1 1 1
10 1 7
```
### 输出
```
YES
NO
NO
```

### 算法分类
数学

### 题解综合分析与结论
这些题解思路基本一致，都基于每7次射击为一轮，一轮能造成9点伤害这一特性。核心要点是判断怪物总生命值是否为9的倍数，以及平均每轮每个怪物承受的伤害是否不超过怪物生命值的最小值，以此确定能否用同一次强化射击杀死所有怪物。各题解在代码实现上略有不同，如输入方式、函数定义等，但整体逻辑相同。

### 所选的题解
 - **作者：Locklink (5星)**
    - **关键亮点**：思路清晰简洁，直接分析出每轮伤害为9，得出总生命值需是9的倍数且平均伤害不超过最小生命值的结论，代码简洁明了。
    ```cpp
    #include<bits/stdc++.h>
    using namespace std;
    int main(){
        int T;
        cin>>T;
        while(T--){
            int a,b,c;
            cin>>a>>b>>c;
            int sum=a+b+c;
            if(sum%9==0&&sum/9<=min(a,min(b,c))){
                cout<<"YES"<<endl;
            }
            else{
                cout<<"NO"<<endl;
            }
        }
    }
    ```
 - **作者：gyh20 (4星)**
    - **关键亮点**：同样思路清晰，采用模拟的思想，先判断总血量是否为9的倍数，再判断总轮数与最小血量的关系，代码中使用了一些输入优化。
    ```cpp
    #pragma GCC optimize("Ofast")
    #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
    #pragma GCC optimize("unroll-loops")
    #pragma GCC optimize(2)
    #pragma GCC optimize(3)
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("inline")
    #include<cstdio>
    #include<algorithm>
    #define re register
    using namespace std;
    const int Mxdt=500000;	//单次大小 
    inline char gc(){
        static char buf[Mxdt],*p1=buf,*p2=buf;
        return p1==p2&&(p2=(p1=buf)+fread(buf,1,Mxdt,stdin),p1==p2)?EOF:*p1++;
    }
    #define gc getchar
    inline int read(){
        re int t=0;re char v=gc();
        while(v<='0')v=gc();
        while(v>='0')t=(t<<3)+(t<<1)+v-48,v=gc();
        return t;
    }
    int n,a,b,c,t;
    int main(){
        t=read();
        while(t--){
            a=read(),b=read(),c=read();
            if((a+b+c)%9)puts("NO");
            else{
                int d=min(min(a,b),c);
                if(d<(a+b+c)/9)puts("NO");
                else puts("YES");
            }
        }
    }
    ```
 - **作者：Time_tears (4星)**
    - **关键亮点**：简洁地分析出答案为YES的两个必要条件，即总生命值是9的倍数且平均伤害不超过最小生命值，代码逻辑清晰。
    ```cpp
    #include<bits/stdc++.h>
    using namespace std;
    int T,a,b,c;
    inline int read() {
        int s=0,f=0;
        char ch=getchar();
        while(ch<48||ch>57)f=(ch=='-'),ch=getchar();
        while(ch>47&&ch<58)s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
        return f?-s:s;
    }
    int main() {
        T=read();
        while(T--) {
            a=read(),b=read(),c=read();
            int sum=a+b+c,tmp=min(min(a,b),c);
            if(sum%9!=0)puts("NO");
            else if(sum/9>tmp)puts("NO");
            else puts("YES");
        }
        return 0;
    }
    ```

### 最优关键思路或技巧
通过分析射击规律得出每轮固定伤害为9，从而将问题转化为对怪物总生命值和最小生命值的数学判断，简化问题求解过程。

### 可拓展之处
同类型题可考虑改变射击周期、伤害值、怪物数量等条件，类似算法套路是通过分析周期性操作对总状态的影响，建立数学关系来判断结果。

### 洛谷相似题目
 - [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)
 - [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)
 - [P2669 金币](https://www.luogu.com.cn/problem/P2669)

### 个人心得摘录与总结
无。 

---
处理用时：44.00秒