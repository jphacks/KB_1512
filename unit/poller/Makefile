.PHONY: transfer

transfer:
	scp ./package.json edison1:~/src/unit/poller/package.json
	scp ./index.js edison1:~/src/unit/poller/index.js
	ssh edison1 'cd ~/src/unit/poller && node index.js'
