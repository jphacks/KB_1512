require "sinatra"
require "sinatra/reloader" if development?
require 'active_record'
require 'json'
require 'mysql2'
#require 'omniauth-twitter'
#require 'twitter'

#mysql
ActiveRecord::Base.configurations = YAML.load_file('database.yml')
ActiveRecord::Base.establish_connection('development')

class User < ActiveRecord::Base
end

#Time out error
after do
  ActiveRecord::Base.connection.close
end

#########################################################################################

get '/' do
	"Hello World"
end


get '/home' do
	erb :home
end

get '/water' do
	erb :water
end

get '/register' do
	erb :register
end

post '/register' do
	user = User.new
	user.name = params[:name]
	user.email = params[:mail]
	user.password = params[:pass]
	user.save
	redirect '/home'
end

get '/login' do
	erb :login
end

post '/login' do
	'login'
end




