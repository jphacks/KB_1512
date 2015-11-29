require "sinatra"
require "sinatra/reloader" if development?
require 'active_record'
require 'json'
require 'mongoid'

#sqlite
ActiveRecord::Base.configurations = YAML.load_file('database.yml')
ActiveRecord::Base.establish_connection('development')

class User < ActiveRecord::Base
end
class Command < ActiveRecord::Base
end

class Sensed
  include Mongoid::Document
	field :uuid, type: String
	field :timestamp, type: Integer
	field :humidity, type: Float
	field :temperature, type: Float
end

Mongoid.load!('mongoid.yml', :development)

#Time out error
after do
  ActiveRecord::Base.connection.close
end

enable :sessions

before do
	unless session[:id].to_s.empty? then
		@id = session[:id]
	end
end

#########################################################################################

get '/' do
	"Hello World"
end


get '/home' do
	erb :home
end

get '/water/:id' do
	unless session[:id].to_s.empty? then
		@data = Sensed.find(uuid: "68f34807-55ce-454d-8302-b718caf9c0c0").first
		erb :water	
	else
		erb :login
	end
end

get '/water/' do
	redirect :login
end

post '/water/:id' do
	command = Command.new
	command.id = params[:user_id]
	command.date = params[:today_time]
	command.command = 0
	command.save
end

get '/getcommand/:id' do
	command = Command.find_by_id(params[:id]);
	command.delete
	command_tmp = command.to_json
	puts command
	return command_tmp
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
	unless session[:id].to_s.empty? then
		redirect "water/" + session[:id].to_s
	else
		erb :login
	end
end

post '/login' do
	user = User.find_by_email(params[:mail])
	if params[:pass] == user.password then
		session[:id] = user.id
		redirect "water/" + user.id.to_s
	else
		redirect "login"
	end	
end

get '/logout' do
	unless session[:id].to_s.empty? then
		session.clear
	end
	redirect 'home'
end



