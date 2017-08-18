# Sagitta: Endless Runner
An infinite, networked runner in C++. 

## Contribute
The workflow goes like this: each coder works in his/her own main branch outside master. From there, create a new branch for each feature. When the feature is done, merge it into your main branch (not master) and make a pull request on GitHub.

### Steps
- clone, fetch, or pull the project from repository (depending on the state of your local code)
- from master, make a main branch for your work (git checkout -b your-branch-name). Do not ever delete this one
- from your branch, for each feature you implement, make a feature branch (git checkout -b your-feature-name)
- make changes in your feature branch, add, commit
- if there have been changes in master since you started, merge master and test (git merge master)
- when your feature is done, merge into your main branch (git checkout your-branch-name, git merge your-feature-name)
- push to the repository (git push -u origin HEAD)
- initiate a pull request in GitHub when your changes are ready to be reviewed
- after your pull request is accepted, delete your feature branch (git branch -d your-feature-name)

## Build the client
On unix-like systems, call `make` from the source directory. You will need the ncurses library and C++11 support on your system.

## Build the server
On unix-like systems, call `make server` from the source directory.

## Client Usage
Call `./runner [ <ip> <port> ]` from the binaries/runner directory.

## Server Usage
Call `./server [ <port> ]` from the binaries/server directory.
