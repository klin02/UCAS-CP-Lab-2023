# CPLab配置

### 个人分支和master分支的同步

1. 创建分支
   ```shell
   git checkout -b xxx
   //第一次提交为本地分支创建相应远程分支
   git push --set-upstream origin xxx
   //之后的提交
   git push origin xxx
   ```

2. 运行脚本的要求

   + 在个人分支下完成git add .和git commit
   + cact目录下运行`sh s2m.sh xxx`将个人分支进度同步到master
   + cact目录下运行`sh m2s.sh xxx`将master分支进度同步到个人分支



### 在bash提示符中显示当前分支

将~/.bashrc中的

```shell
if [ "$color_prompt" = yes ]; then
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
else
    PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
fi
unset color_prompt force_color_prompt

```

更改为

```shell
show_git_branch() {
 git branch 2> /dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/(\1)/'
}

if [ "$color_prompt" = yes ]; then
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[01;32m\]$(show_git_branch)\[\033[00m\]\$ '
else
    PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w$(show_git_branch)\$ '
fi
unset color_prompt force_color_prompt
```



### 环境的配置

+ java配置：需要java版本在1.6.0以上

  ```shell
  sudo apt-get install openjdk-8-jre
  ```

+ 忽视本机修改依赖对远程仓库的影响

  notes目录下执行

  ```shell
  sh ignore-deps.sh
  ```

  + 原理：通过`git update-index --skip-worktree <filename>`可以让git认为这个文件始终处于最新提交状态（跟踪文件状态，不跟踪具体状态）。因此，不会在checkout切换分支或者git push 提交时产生影响。
  + 注意：该方法要求远程仓库的deps不会进行修改，否则在git pull时会更新到远程仓库的内容。这需要保证每个人在配置自己环境时都先执行本脚本。

+ 本机产生cact项目编译相关依赖

  notes目录下执行

  ```shell
  sh myenv.sh
  ```

  + 注意：先执行`sh ignore-deps.sh`
  + 原理：实验一在服务器目录下执行的cmake使用了绝对路径，使得本机的依赖路径不同。该脚本在本机路径下执行cmake和make，使得本机可以编译cact项目。
  + 测试：将cact项目删除build文件夹和grammar文件夹中除Hello.g4外文件，然后重复PR001实验说明的第三步跑通demo。注意，由于后续实验需要修改代码，不再保留demo的分支，请另外clone一个项目，并使用`git checkout fb8aaf2abb33e7aff031529c89db7206f309a60d`切换到之前的提交。测试完毕后删除该项目即可。
  + 见上一点，deps更改不会上传到仓库，每个人执行该脚本对其他人没有影响

+ 查看打了标识的文件

  ```shell
  git ls-files -v | grep -i ^S
  ```

+ 其他说明：

  不同电脑上由于依赖不同，编译cact项目时的build也会有一定差异，不过一方面该文件夹小，改动消耗少，而且随着.g4文件的修改也会频繁改动，因此不需要使用上述方法进行忽视。