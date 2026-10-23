# Data-Structures-Homeworks
I don't know what to write here yet

## How to use makefile (for windows):
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

If SecurityError, run Powershell as administrator, type in:
```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
```
Then press `y` and `ENTER`.
