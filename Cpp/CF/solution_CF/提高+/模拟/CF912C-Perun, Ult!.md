# Perun, Ult!

## 题目描述

A lot of students spend their winter holidays productively. Vlad has advanced very well in doing so! For three days already, fueled by salads and tangerines — the leftovers from New Year celebration — he has been calibrating his rating in his favorite MOBA game, playing as a hero named Perun.

Perun has an ultimate ability called "Thunderwrath". At the instant of its activation, each enemy on the map ( $ n $ of them in total) loses ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912C/d216f79c4581ff07bac2eb40367610feb8c137c2.png) health points as a single-time effect. It also has a restriction: it can only activated when the moment of time is an integer. The initial bounty for killing an enemy is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912C/2078a0964de47cdee5ccf9b3fbbb9c2602fdb150.png). Additionally, it increases by ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912C/600a44120274d855b208352694b857991b9552e9.png) each second. Formally, if at some second $ t $ the ability is activated and the $ i $ -th enemy is killed as a result (i.e. his health drops to zero or lower), Vlad earns ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912C/2affc6d4bcb10dc0ae3b3c9c0c973c94780f368d.png) units of gold.

Every enemy can receive damage, as well as be healed. There are multiple ways of doing so, but Vlad is not interested in details. For each of $ n $ enemies he knows:

- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912C/fc4707d8a855c477b62b13b1470d38bb6766fbc9.png) — maximum number of health points for the $ i $ -th enemy;
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912C/8efcccd354ad1e78851168f9dfe9981ef086b631.png) — initial health of the enemy (on the $ 0 $ -th second);
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912C/dce4274c465d132023523d8a7f53bc4a706d2722.png) — the amount of health the $ i $ -th enemy can regenerate per second.

There also $ m $ health updates Vlad knows about:

- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912C/085949a0fef92cec2ad6a8413640d4367b22ea30.png) — time when the health was updated;
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912C/b2ad7de3b3b780b7804e20a0428f7e5181e4453b.png) — the enemy whose health was updated;
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912C/fa9c2a28c567ce2c3bc995acf7706c9f11229fd1.png) — updated health points for $ enemy_{j} $ .

Obviously, Vlad wants to maximize his profit. If it's necessary, he could even wait for years to activate his ability at the right second. Help him determine the exact second (note that it must be an integer) from $ 0 $ (inclusively) to $ +∞ $ so that a single activation of the ability would yield Vlad the maximum possible amount of gold, and print this amount.

## 说明/提示

On the pictures you can see health points of each enemy versus time in sample cases.

Periods when Vlad can kill one enemy are marked with yellow color.

Periods when Vlad can kill two enemies are marked with purple color.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912C/371bebe0ea750379826870ee127df5b588d49620.png)In the first sample case, Vlad can activate the ability at the $ 50 $ -th second: the enemies $ 2 $ and $ 3 $ will die since they would have $ 40 $ and $ 50 $ health points correspondingly. Vlad will earn $ 2·(1000+50·10)=3000 $ gold.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912C/dee22bf9a2821d482ba5ff5de6e1cf1db497ba51.png)In the second sample case, the maximum amount of health for the enemy $ 1 $ is less than the damage dealt by the ability. Hence, the enemy could be killed anytime. As the bounty increases by $ 50 $ over the time, the maximum possible amount of gold is infinite.

## 样例 #1

### 输入

```
3 2
1000 10 50
70 5 5
90 70 1
110 20 2
20 2 10
30 3 10
```

### 输出

```
3000
```

## 样例 #2

### 输入

```
1 1
500 50 1000
750 750 20
10 1 300
```

### 输出

```
-1
```

