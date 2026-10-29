# Data-Structures-Homeworks
I don't know what to write here yet

## How to use this project's makefile:
### Compile all:
```powershell
make all
```

### Compile a specific source in main root directory:
```powershell
make <source name (without .cpp)>
```

### Compile all the sources in a sub directory:
```powershell
make <directory name>
```

## How to setup make (for windows):
Make sure `make` is installed:
```powershell
mingw32-make --version
```

### For Powershell:
Set alias for `make`:
```powershell
# Set alias
Set-Alias -Name make -Value mingw32-make

# Confirm
alias make

# Test
make --version
```

To make the alias permanent:

Edit `$PROFILE` 

(`$ENV:USERPROFILE\Documents\WindowsPowerShell\Microsoft.PowerShell_profile.ps1`):
```powershell
# Notepad
notepad $PROFILE

# Vim
vim $PROFILE
```

If SecurityError, run Powershell as administrator, type in the below command:
```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
```
Then press `y` and `ENTER`.
