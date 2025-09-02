# 题目信息

# Chord

## 题目描述

Vasya studies music.

He has learned lots of interesting stuff. For example, he knows that there are 12 notes: C, C#, D, D#, E, F, F#, G, G#, A, B, H. He also knows that the notes are repeated cyclically: after H goes C again, and before C stands H. We will consider the C note in the row's beginning and the C note after the H similar and we will identify them with each other. The distance between the notes along the musical scale is measured in tones: between two consecutive notes there's exactly one semitone, that is, 0.5 tone. The distance is taken from the lowest tone to the uppest one, that is, the distance between C and E is 4 semitones and between E and C is 8 semitones

Vasya also knows what a chord is. A chord is an unordered set of no less than three notes. However, for now Vasya only works with triads, that is with the chords that consist of exactly three notes. He can already distinguish between two types of triads — major and minor.

Let's define a major triad. Let the triad consist of notes $ X $ , $ Y $ and $ Z $ . If we can order the notes so as the distance along the musical scale between $ X $ and $ Y $ equals 4 semitones and the distance between $ Y $ and $ Z $ is 3 semitones, then the triad is major. The distance between $ X $ and $ Z $ , accordingly, equals 7 semitones.

A minor triad is different in that the distance between $ X $ and $ Y $ should be 3 semitones and between $ Y $ and $ Z $ — 4 semitones.

For example, the triad "C E G" is major: between C and E are 4 semitones, and between E and G are 3 semitones. And the triplet "C# B F" is minor, because if we order the notes as "B C# F", than between B and C# will be 3 semitones, and between C# and F — 4 semitones.

Help Vasya classify the triad the teacher has given to him.

## 样例 #1

### 输入

```
C E G
```

### 输出

```
major
```

## 样例 #2

### 输入

```
C# B F
```

### 输出

```
minor
```

## 样例 #3

### 输入

```
A B H
```

### 输出

```
strange
```

# AI分析结果

### 题目翻译
# 和弦

## 题目描述
Vasya正在学习音乐。

他学到了很多有趣的东西。例如，他知道有12个音符：C、C#、D、D#、E、F、F#、G、G#、A、B、H。他还知道这些音符是循环重复的：H之后又是C，C之前是H。我们会认为排在序列开头的C和H之后的C是相同的，并将它们视为同一个音符。音符在音阶上的距离用半音来衡量：相邻两个音符之间恰好有一个半音，即0.5个全音。距离是从低音到高音来计算的，也就是说，C和E之间的距离是4个半音，E和C之间的距离是8个半音。

Vasya也知道什么是和弦。和弦是一个由不少于三个音符组成的无序集合。不过，目前Vasya只研究三和弦，即恰好由三个音符组成的和弦。他已经能够区分两种类型的三和弦——大调和小调。

让我们来定义一下大调和弦。假设这个三和弦由音符 $X$、$Y$ 和 $Z$ 组成。如果我们可以对这些音符进行排序，使得音阶上 $X$ 和 $Y$ 之间的距离等于4个半音，$Y$ 和 $Z$ 之间的距离是3个半音，那么这个三和弦就是大调的。相应地，$X$ 和 $Z$ 之间的距离等于7个半音。

小调和弦的不同之处在于，$X$ 和 $Y$ 之间的距离应该是3个半音，$Y$ 和 $Z$ 之间的距离是4个半音。

例如，三和弦 “C E G” 是大调的：C和E之间有4个半音，E和G之间有3个半音。而三和弦 “C# B F” 是小调的，因为如果我们将音符排序为 “B C# F”，那么B和C#之间将有3个半音，C#和F之间有4个半音。

帮助Vasya对老师给他的三和弦进行分类。

## 样例 #1
### 输入
```
C E G
```
### 输出
```
major
```

## 样例 #2
### 输入
```
C# B F
```
### 输出
```
minor
```

## 样例 #3
### 输入
```
A B H
```
### 输出
```
strange
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是先将输入的音符字符串转换为对应的数字编号，然后对这些编号进行排序，再根据大调和弦与小调和弦的距离规则进行判断。如果一次判断不满足条件，就将最小的音符编号加12（提高八度），重新排序后再次判断，最多进行三次这样的操作，若都不满足则判定为 “strange”。

不同题解的差异主要在于代码实现的细节，如音符编号转换的方式、排序的方法、判断循环的实现等。大部分题解使用了 `sort` 函数进行排序，部分题解使用冒泡排序。在音符编号转换上，有的使用数组存储音符与编号的对应关系，有的使用多个 `if-else` 语句。

### 所选题解
- **作者：Zachary_Cloud (赞：5)，4星**
    - **关键亮点**：思路清晰，代码简洁，使用数组存储音符与编号的对应关系，通过循环将音符转换为编号，排序后进行判断，逻辑明确。
    - **个人心得**：提到题目中的 $|XY|$ 容易误解为乘积的绝对值，实际是差的绝对值，提醒读者注意题目细节。
- **作者：WNico (赞：4)，4星**
    - **关键亮点**：对题意理解准确，代码中使用函数将音符转换为编号，并且使用 `std::ios::sync_with_stdio(false)` 和 `cin.tie(0)` 加速输入，提高效率。
    - **个人心得**：指出输入的音符不一定按顺序，需要排序，若判断为 “strange” 需将最小的音高八度比对，并说明这与乐理知识有关。
- **作者：yangyuanxi44 (赞：4)，4星**
    - **关键亮点**：明确指出这是一道模拟题，代码结构清晰，使用函数进行音符编号转换，通过循环枚举三种情况进行判断。
    - **个人心得**：提到需要一定的乐理知识，对于将最小的编号加12的操作，说明是乐理知识，但未详细解释。

### 重点代码
#### Zachary_Cloud的核心代码
```cpp
string gett[13] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "B", "H"};
string c1, c2, c3;
int a[4];
int main() {
    cin >> c1 >> c2 >> c3;
    for (int i = 0; i < 13; ++i) { //转为数字
        if (c1 == gett[i]) a[1] = i;
        if (c2 == gett[i]) a[2] = i;
        if (c3 == gett[i]) a[3] = i;
    }
    for (int i = 1; i <= 3; ++i) {
        sort(a + 1, a + 4); //排序
        if ((abs(a[1] - a[2]) == 4 && abs(a[2] - a[3]) == 3)) {cout << "major" << endl; return 0;} //判断为 major
        else if ((abs(a[1] - a[2]) == 3 && abs(a[2] - a[3]) == 4)) {cout << "minor" << endl; return 0;} //判断为 minor
        a[1] += 12; //第一个音符+=12
    }
    cout << "strange" << endl; //strange
    return 0;
}
```
**核心实现思想**：先将输入的音符字符串转换为对应的数字编号，存储在数组 `a` 中，然后对数组进行排序，根据大调和弦与小调和弦的距离规则进行判断，若不满足则将最小的音符编号加12，再次排序判断，最多进行三次，若都不满足则输出 “strange”。

#### WNico的核心代码
```cpp
int rep(string s){ //音符转为数字
    if(s=="C") return 1;
    else if(s=="C#") return 2;
    else if(s=="D") return 3;
    else if(s=="D#") return 4;
    else if(s=="E") return 5;
    else if(s=="F") return 6;
    else if(s=="F#") return 7;
    else if(s=="G") return 8;
    else if(s=="G#") return 9;
    else if(s=="A") return 10;
    else if(s=="B") return 11;
    else if(s=="H") return 12;
    else return 0;
}
int main(){
    std::ios::sync_with_stdio(false);
    cin.tie(0); //cin加速
    string note;
    int a[3];
    cin>>note;
    a[0]=rep(note);
    cin>>note;
    a[1]=rep(note);
    cin>>note;
    a[2]=rep(note);
    sort(a,a+3);
    int ans=0,cnt=3;
    while(!ans&&cnt){
        if(a[2]-a[0]==7){
            if(a[1]-a[0]==4) ans=1; //判断major
            else if(a[1]-a[0]==3) ans=2; //判断minor
        }
        a[0]+=12;
        sort(a,a+3);
        cnt--;
    }
    if(ans==1) cout<<"major";
    else if(ans==2) cout<<"minor";
    else cout<<"strange";
    return 0;
}
```
**核心实现思想**：定义函数 `rep` 将音符字符串转换为对应的数字编号，输入音符并转换后进行排序，通过循环判断是否满足大调和弦或小调和弦的条件，若不满足则将最小的音符编号加12，重新排序判断，最多进行三次，根据结果输出相应的和弦类型。

#### yangyuanxi44的核心代码
```cpp
int change(string s){ //转换
    if(s=="C")  return 1;
    if(s=="C#") return 2;
    if(s=="D")  return 3;
    if(s=="D#") return 4;
    if(s=="E")  return 5;
    if(s=="F")  return 6;
    if(s=="F#") return 7;
    if(s=="G")  return 8;
    if(s=="G#") return 9;
    if(s=="A")  return 10;
    if(s=="B")  return 11;
    if(s=="H")  return 12;
}
int main(){
    cin>>s1>>s2>>s3;
    music[1]=change(s1),music[2]=change(s2),music[3]=change(s3);
    sort(music+1,music+3+1);
    int T=3;
    while(T--){ //枚举3种情况
        if(music[2]-music[1]==4&&music[3]-music[2]==3){
            cout<<"major"<<endl,flag=1;
            break;
        }
        else if(music[2]-music[1]==3&&music[3]-music[2]==4){
            cout<<"minor"<<endl,flag=2;
            break;
        }
        else{
            music[1]+=12; //不符合+12
            sort(music+1,music+1+3);
        }
    }
    if(!flag)
        cout<<"strange"<<endl;
    return 0;
}
```
**核心实现思想**：定义函数 `change` 将音符字符串转换为对应的数字编号，输入音符并转换后进行排序，通过循环枚举三种情况，根据大调和弦与小调和弦的距离规则进行判断，若不满足则将最小的音符编号加12，重新排序判断，若都不满足则输出 “strange”。

### 最优关键思路或技巧
- **音符编号转换**：使用数组或多个 `if-else` 语句将音符字符串转换为对应的数字编号，方便后续的距离计算和判断。
- **排序**：对音符编号进行排序，避免使用绝对值计算距离，简化判断逻辑。
- **提高八度**：当一次判断不满足条件时，将最小的音符编号加12（提高八度），重新排序后再次判断，最多进行三次，考虑到音符的循环特性。

### 可拓展之处
同类型题可能会涉及更多音符组成的和弦分类，或者不同的音乐规则判断。类似算法套路主要是模拟，根据给定的规则进行数据处理和判断，可能会结合字符串处理、排序等操作。

### 推荐题目
- [P1000 超级玛丽游戏](https://www.luogu.com.cn/problem/P1000)：简单的模拟题，锻炼基本的编程能力和逻辑思维。
- [P1001 A+B Problem](https://www.luogu.com.cn/problem/P1001)：基础的输入输出和简单运算题，适合初学者熟悉编程环境。
- [P1425 小鱼的游泳时间](https://www.luogu.com.cn/problem/P1425)：模拟时间计算的题目，与本题的模拟思路类似。

### 个人心得摘录与总结
- Zachary_Cloud：提醒注意题目中符号的含义，避免误解，做题时要仔细读题，注意细节。
- WNico：指出输入顺序可能无序，需要排序，以及涉及乐理知识的特殊处理，说明做题时要全面理解题意，考虑各种情况。
- yangyuanxi44：提到需要一定的乐理知识，但未详细解释，提示对于涉及专业知识的题目，要适当了解相关背景知识。

---
处理用时：73.54秒