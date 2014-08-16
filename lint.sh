find . -name *.hpp -o -name *.cpp  | xargs python cpplint.py --extensions=hpp,cpp --linelength=100 --filter=-readability/streams,-build/namespaces,-readability/braces,-readability/casting,-legal/copyright
exit 0
