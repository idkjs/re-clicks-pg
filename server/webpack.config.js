const config = {
	mainServer: './src/server/index.ts',
	start_url: '/graphiql',
	dir: 'auto',
	lang: 'en'
};

const webpackNodeExternals = require('webpack-node-externals');
const WriteFileWebpackPlugin = require('write-file-webpack-plugin');
const ReloadServerWebpackPlugin = require('reload-server-webpack-plugin');

const isProd = process.env.NODE_ENV === 'production';

module.exports = [
	{
		mode:
			isProd ? 'production' :
			'development',
		entry: config.mainServer,
		output: { path: __dirname + '/dist', filename: '[name].js' },
		target: 'node',
		module: {
			rules: [
				{
					test: /\.[jt]s$/,
					loader: 'babel-loader',
					options: {
						presets: [
							'@babel/preset-typescript'
						]
					}
				}
			]
		},
		resolve: {
			extensions: [
				'.js',
				'.ts'
			]
		},
		plugins: [
			!isProd && new WriteFileWebpackPlugin(),
			!isProd && new ReloadServerWebpackPlugin({ script: 'dist/main.js' })
		].filter((v) => v),
		externals: [
			webpackNodeExternals()
		]
	}
];
