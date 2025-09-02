# 题目信息

# Music

## 题目描述

Little Lesha loves listening to music via his smartphone. But the smartphone doesn't have much memory, so Lesha listens to his favorite songs in a well-known social network InTalk.

Unfortunately, internet is not that fast in the city of Ekaterinozavodsk and the song takes a lot of time to download. But Lesha is quite impatient. The song's duration is $ T $ seconds. Lesha downloads the first $ S $ seconds of the song and plays it. When the playback reaches the point that has not yet been downloaded, Lesha immediately plays the song from the start (the loaded part of the song stays in his phone, and the download is continued from the same place), and it happens until the song is downloaded completely and Lesha listens to it to the end. For $ q $ seconds of real time the Internet allows you to download $ q-1 $ seconds of the track.

Tell Lesha, for how many times he will start the song, including the very first start.

## 说明/提示

In the first test, the song is played twice faster than it is downloaded, which means that during four first seconds Lesha reaches the moment that has not been downloaded, and starts the song again. After another two seconds, the song is downloaded completely, and thus, Lesha starts the song twice.

In the second test, the song is almost downloaded, and Lesha will start it only once.

In the third sample test the download finishes and Lesha finishes listening at the same moment. Note that song isn't restarted in this case.

## 样例 #1

### 输入

```
5 2 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 4 7
```

### 输出

```
1
```

## 样例 #3

### 输入

```
6 2 3
```

### 输出

```
1
```

# AI分析结果



# 中文题目重写

### 题目描述  
小Lesha喜欢通过智能手机听歌，但手机内存不足，因此他使用社交网络InTalk边下载边播放。歌曲总时长为$T$秒，初始下载了前$S$秒。播放时若遇到未下载部分会立即重头开始播放（已下载部分保留，继续下载）。每实际经过$q$秒，歌曲会多下载$q-1$秒的内容。求Lesha总共启动播放的次数（包括第一次）。

### 输入格式  
输入三个整数$T$, $S$, $q$。

### 输出格式  
输出一个整数表示启动次数。

### 样例  
#### 样例1  
输入：  
5 2 2  
输出：  
2  

#### 样例2  
输入：  
5 4 7  
输出：  
1  

---

**算法分类**  
数学、模拟

---

### 题解综合分析  
所有题解均通过数学推导得出核心规律：每次播放结束时，已下载时长会扩展为当前值的$q$倍。通过循环乘$q$并计数，直到覆盖总时长$T$。该问题的核心在于将下载速度转换为等比数列模型。

---

### 精选题解及评分

#### 1. 题解作者：qifan_maker（4星）  
**亮点**  
- 代码简洁，直接体现核心逻辑  
- 明确将下载速度转换为等比增长模型  
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t,s,q;
    cin >> t >> s >> q;
    int cnt=0;
    while (s<t){
        s *= q;
        cnt++;
    }
    cout << cnt;
}
```

#### 2. 题解作者：JZH123（4星）  
**亮点**  
- 方程式推导过程清晰  
- 代码与数学模型的对应关系明确  
```cpp
#include<bits/stdc++.h>
using namespace std;
int T, s, q, cnt;
int main() {
    scanf ("%d%d%d", &T, &s, &q);
    while (s < T) {
        s *= q;
        cnt ++;
    } 
    printf ("%d", cnt);
    return 0;
}
```

---

### 关键思路总结  
**核心数学模型**：  
每轮播放结束时，已下载时长满足 $s_{new} = s_{old} \times q$。这是因为在播放$s$秒的时间内（需现实时间$s$秒），下载了$(q-1)/q \times s$秒内容，总下载量变为 $s + (q-1)s = s \times q$。

---

### 同类题目推荐  
1. [P1029 最大公约数和最小公倍数](https://www.luogu.com.cn/problem/P1029)  
   - 考察数学推导与循环条件设计  
2. [P1226 快速幂](https://www.luogu.com.cn/problem/P1226)  
   - 涉及幂次增长的快速计算技巧  
3. [P1036 选数](https://www.luogu.com.cn/problem/P1036)  
   - 组合数学与边界条件处理

---
处理用时：92.85秒