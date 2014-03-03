#Deploying
#
desc "commit"
task :push do 
	puts "\n ## staging modified files"
	status = system ("git add .")
	puts status ? "Success" : "Failed"
	puts "\n ## commit at #{Time.now}"
	message = "Build at #{Time.now}"
	status = system("git commit -m \"#{message}\"")
	puts status ? "Success" : "Failed"
	puts "\n## Pushing commits to remote"
	status = system("git push")
	if status 
		puts "Success"	
	else 
		puts "pull again for latest version"
		status = system("git pull; git push")
		puts status ? "Success" : "Failed"
	end
end
